#include <fstream>
#include <string>

#include <SFML/Audio/SoundBuffer.hpp>

#include <libmodplug/modplug.h>

#include "content/xmSound.h"
#include "core/staticconstructor.h"

namespace content{
  
  STATIC_INIT()
  {
    ModPlug_Settings modSettings;
    ModPlug_GetSettings(&modSettings);
    modSettings.mBits = 16;
    ModPlug_SetSettings(&modSettings);
  }
  
  static bool parseXMFile(const std::string &path, ModPlugFile *&mod)
  {
    // first we read the whole file (modFile) into a buffer (fileData)
    std::ifstream modFile(path.c_str(), std::ifstream::in | std::ifstream::binary);
    
    if(!modFile.is_open())
      return false;

    modFile.seekg(0, std::ifstream::end);
    const std::streampos fileSize = modFile.tellg();
    modFile.seekg(0, std::ifstream::beg);

    char *fileData = new char[fileSize];
    modFile.readsome(fileData, fileSize);
    
    if(!modFile)
    {
      delete[] fileData;
      return false;
    }

    modFile.close();

    // now we let modplug handle this data
    mod = ModPlug_Load(fileData, fileSize);
    delete[] fileData;
    
    if(!mod)
      return false;
    
    return true;
  }

  bool openXMFile(const std::string &path, sf::SoundBuffer &buf)
  {
    ModPlugFile *mod;
    if(!parseXMFile(path, mod))
      return false;
      
    ModPlug_Settings modSettings;
    ModPlug_GetSettings(&modSettings);

    // one sample (a single sound so to say) is made up out of the bits per individual sound * number of channels (mono, stereo, ..)
    const int sampleSize = modSettings.mChannels * (modSettings.mBits / 8);
    const int guessedSize = modSettings.mFrequency * sampleSize * (ModPlug_GetLength(mod) * 0.001f);
    std::vector<char> samples;
    samples.reserve(guessedSize);

    char *sample = new char[sampleSize];
  
    // ModPlug_GetLength deems itself unreliable; it is not said how. It will lead to appended silence if guessed length > actual length
    // we read only sample by sample, to be safe. Non-streamed content loading should not be done in a performance-critical area anyways.
#if 0
    ModPlug_Read(mod, sample, guessedSize);
    samples.insert(samples.end(), sample, sample + guessedSize);
#endif
    
    // OBSOLETE | we already allocated memory, why reallocate to something smaller?
#if 0
    delete[] sample;
    sample = new char[sampleSize];
#endif
    
    // while something was read, store it in vector
    while(ModPlug_Read(mod, sample, sampleSize))
      samples.insert(samples.end(), sample, sample + sampleSize);
    
    ModPlug_Unload(mod);
    delete[] sample;

    //  http://www.open-std.org/jtc1/sc22/wg21/docs/lwg-defects.html#69
#if 0
    char* sampleArray = new char[samples.size()];
    std::copy(samples.begin(), samples.end(), sampleArray);
#endif
    // we just convert to sf::Int16* (16-bit samples); as sizeof(sf::Int16) > sizeof(char) we also need take care of the new size
    return buf.LoadFromSamples(reinterpret_cast<const sf::Int16*>(&samples.front()), samples.size() / sizeof(sf::Int16), modSettings.mChannels, modSettings.mFrequency);
  }
  
  XMStream::XMStream()
    :samples(NULL){}

  XMStream::~XMStream()
  {
    delete[] samples;
    
    // GetSampleRate is an indicator if a sound was present
    if(GetSampleRate() != 0)
      ModPlug_Unload(mod);
  }
  
  bool XMStream::Open(const std::string &path)
  {
    if(!parseXMFile(path, mod))
      return false;
    
    ModPlug_Settings modSettings;
    ModPlug_GetSettings(&modSettings);
    
    singleSampleSize = modSettings.mChannels * (modSettings.mBits / 8);
    samplesSize = singleSampleSize * (modSettings.mFrequency / 10); // 1 / 10 second chunk
    // ^- note: this might cause up to 1 / 10  - (1 / (modSettings.mFrequency / 10)) seconds unwanted silence at the end of the song!
    // ^- I think it's worth it instead of reading sample by sample here ;z33ky
    
    
    Initialize(modSettings.mChannels, modSettings.mFrequency);
    
    return true;
  }
  
  bool XMStream::OnGetData(Chunk& data)
  {
    // char *samples = NULL; // member for workaround for delete[] (see below)
    delete[] samples;
    samples = new char[samplesSize];
    
    // note: in theory, ModPlug_Read should return the number of bytes read, at least it informs us when nothing was read
    data.NbSamples = (ModPlug_Read(mod, samples, samplesSize) / singleSampleSize) * sizeof(sf::Int16);
    data.Samples = reinterpret_cast<sf::Int16*>(samples);
      
    // delete[] samples; // seems to sometimes make problems (only at song start?)?
    //  ^- worked around that ;z33ky
      
    return data.NbSamples != 0;
  }
  
}
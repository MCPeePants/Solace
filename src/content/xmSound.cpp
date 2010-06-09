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

  bool openXMFile(const std::string &path, sf::SoundBuffer &buf)
  {
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
    
    ModPlug_Settings modSettings;
    ModPlug_GetSettings(&modSettings);

    ModPlugFile *mod = ModPlug_Load(fileData, fileSize);
    delete[] fileData;
    
    if(!mod)
      return false;

    const int sampleSize = modSettings.mChannels * (modSettings.mBits / 8);
    std::vector<char> samples;
    const std::vector<char>::size_type guessedSize = modSettings.mFrequency * sampleSize * (ModPlug_GetLength(mod) * 0.001f);
    // FIXME: I guess guessedSize the minimum length, but a guess is a guess ;z33ky
    //   if it's longer it will generate silence at the end
    char *sample = new char[guessedSize];
    
    ModPlug_Read(mod, sample, guessedSize);
    samples.insert(samples.begin(), sample, sample + guessedSize);
    
    // we already allocated memory, why reallocate to something smaller?
#if 0
    delete[] sample;
    sample = new char[sampleSize];
#endif
    
    while(ModPlug_Read(mod, sample, sampleSize))
      samples.insert(samples.end(), sample, sample + sampleSize);
    
    ModPlug_Unload(mod);
    delete[] sample;

    return buf.LoadFromSamples(reinterpret_cast<const sf::Int16*>(samples.data()), samples.size() / sizeof(sf::Int16), modSettings.mChannels, modSettings.mFrequency);
  }
  
  XMStream::XMStream()
    :samples(NULL){}

  XMStream::~XMStream()
  {
    delete[] samples;
    
    if(GetSampleRate() != 0)
      ModPlug_Unload(mod);
  }
  
  bool XMStream::Open(const std::string &path)
  {
    std::ifstream modFile(path.c_str(), std::ifstream::in | std::ifstream::binary);
    
    if(!modFile.is_open())
      return false;

    modFile.seekg(0, std::ifstream::end);
    const std::streampos fileSize = modFile.tellg();
    modFile.seekg(0, std::ifstream::beg);

    char *fileData = new char[fileSize];
    modFile.readsome(fileData, fileSize);
    
    modFile.close();
    
    if(!modFile)
    {
      delete[] fileData;
      return false;
    }
    
    ModPlug_GetSettings(&modSettings);

    mod = ModPlug_Load(fileData, fileSize);
    delete[] fileData;
    
    if(!mod)
      return false;

    sampleSize = modSettings.mChannels * (modSettings.mBits / 8);
    
    Initialize(modSettings.mChannels, modSettings.mFrequency);
    
    return true;
  }
  
  bool XMStream::OnGetData(Chunk& data)
  {
    data.NbSamples = modSettings.mFrequency; // 1 second chunk
    // char *samples = NULL; // member for workaround for delete[] (see below)
    delete[] samples;
    samples = new char[data.NbSamples * sampleSize];
      
    data.NbSamples = (ModPlug_Read(mod, samples, data.NbSamples * sampleSize) / sampleSize) * sizeof(sf::Int16);
    data.Samples = reinterpret_cast<sf::Int16*>(samples);
      
    // delete[] samples; // seems to sometimes make problems (only at song start?)?
    //  ^- worked around that ;z33ky
      
    return data.NbSamples != 0;
  }
  
}
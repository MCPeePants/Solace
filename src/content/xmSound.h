#ifndef SLC_CONTENT_XMSOUND_H
#define SLC_CONTENT_XMSOUND_H

#include <fstream>
#include <string>

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/SoundStream.hpp>

#include <libmodplug/modplug.h>

#include "core/staticconstructor.h"

namespace content{
  
  // TODO: stuff in inline-file ;z33ky
  STATIC_INIT()
  {
    ModPlug_Settings modSettings;
    ModPlug_GetSettings(&modSettings);
    modSettings.mBits = 16; // TODO: probably could do that at initialization-time ;z33ky
    ModPlug_SetSettings(&modSettings);
  }

  static sf::SoundBuffer openXMFile(const std::string &path)
  {
    std::ifstream modFile(path.c_str(), std::ifstream::in | std::ifstream::binary);

    modFile.seekg(0, std::ifstream::end);
    const std::streampos fileSize = modFile.tellg();
    modFile.seekg(0, std::ifstream::beg);

    char *fileData = new char[fileSize];
    modFile.readsome(fileData, fileSize);

    modFile.close();
    
    ModPlug_Settings modSettings;
    ModPlug_GetSettings(&modSettings);

    ModPlugFile *mod = ModPlug_Load(fileData, fileSize);
    delete[] fileData;

    const int sampleSize = modSettings.mChannels * (modSettings.mBits / 8);
    std::vector<char> samples;
    const std::vector<char>::size_type guessedSize = modSettings.mFrequency * sampleSize * (ModPlug_GetLength(mod) * 0.001f);
    // TODO: I guess guessedSize the minimum length, but a guess is a guess ;z33ky
    char *sample = new char[guessedSize];
    
    ModPlug_Read(mod, sample, guessedSize);
    samples.insert(samples.begin(), sample, sample + guessedSize);
    
    delete[] sample;
    sample = new char[sampleSize];
    
    while(ModPlug_Read(mod, sample, sampleSize))
      samples.insert(samples.end(), sample, sample + sampleSize);
    
    ModPlug_Unload(mod);
    delete[] sample;

    sf::SoundBuffer buffer;
    buffer.LoadFromSamples(reinterpret_cast<const sf::Int16*>(samples.data()), samples.size() / sizeof(sf::Int16), modSettings.mChannels, modSettings.mFrequency);
    return buffer;
  }
  
  class XMStream : public sf::SoundStream
  {
  public:
    // note: violating convention
    bool Open(const std::string &path)
    {

      std::ifstream modFile(path.c_str(), std::ifstream::in | std::ifstream::binary);

      modFile.seekg(0, std::ifstream::end);
      const std::streampos fileSize = modFile.tellg();
      modFile.seekg(0, std::ifstream::beg);

      char *fileData = new char[fileSize];
      modFile.readsome(fileData, fileSize);

      modFile.close();
      
      ModPlug_GetSettings(&modSettings);

      mod = ModPlug_Load(fileData, fileSize);
      delete[] fileData;

      sampleSize = modSettings.mChannels * (modSettings.mBits / 8);

      Initialize(modSettings.mChannels, modSettings.mFrequency);

      return true;
    }
    
  private:
    bool OnGetData(Chunk& data)
    {
      data.NbSamples = modSettings.mFrequency; // 1 second chunk
      char *samples = new char[data.NbSamples * sampleSize];
      
      data.NbSamples = (ModPlug_Read(mod, samples, data.NbSamples * sampleSize) / sampleSize) * sizeof(sf::Int16);
      data.Samples = reinterpret_cast<sf::Int16*>(samples);
      
      //delete[] samples; // seems to sometimes make problems (song start?)?
      // TODO: ^- investigate! ;z33ky
      
      return data.NbSamples != 0;
    }
    
    void OnSeek(float timeOffset)
    {
      ModPlug_Seek(mod, timeOffset * 1000);
    }
    
  private:
    ModPlugFile *mod;
    ModPlug_Settings modSettings;
    int sampleSize;
  };

}

#endif
#ifndef SLC_CONTENT_XMSOUND_H
#define SLC_CONTENT_XMSOUND_H

#include <fstream>
#include <string>

#include <SFML/Audio/SoundBuffer.hpp>

#include <libmodplug/modplug.h>

namespace content{

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
    modSettings.mBits = 16; // TODO: probably could do that at initialization-time ;z33ky
    ModPlug_SetSettings(&modSettings);

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
    
    while(ModPlug_Read(mod, sample, modSettings.mChannels * (modSettings.mBits / 8)))
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
    static sf::SoundStream open(const std::string &path)
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
      modSettings.mBits = 16; // TODO: probably could do that at initialization-time ;z33ky
      ModPlug_SetSettings(&modSettings);

      ModPlugFile *mod = ModPlug_Load(fileData, fileSize);
      delete[] fileData;

      const int sampleSize = modSettings.mChannels * (modSettings.mBits / 8);
    }
    
  private:
    bool OnGetData(Chunk& data)
    {
      
    }
    
    void OnSeek(float timeOffset)
    {
      
    }
    
  private:
    
  }

}

#endif
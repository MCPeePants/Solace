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
    const std::streampos filesize = modFile.tellg();
    modFile.seekg(0, std::ifstream::beg);

    char *filedata = new char[filesize];
    modFile.readsome(filedata, filesize);

    modFile.close();
    
    ModPlug_Settings modSettings;
    ModPlug_GetSettings(&modSettings);
    modSettings.mBits = 16; // TODO: probably could do that at initialization-time ;z33ky
    ModPlug_SetSettings(&modSettings);

    ModPlugFile *mod = ModPlug_Load(filedata, filesize);
    delete[] filedata;

    std::vector<char> data;
    data.reserve(modSettings.mFrequency * modSettings.mChannels * (modSettings.mBits / 8) * (ModPlug_GetLength(mod) * 0.001f)); // TODO: trust ModPlug_GetLength enough? ;z33ky
    char *single = new char[modSettings.mChannels * (modSettings.mBits / 8)];
    
    // TODO: we can make this a little more efficient ;z33ky
    while(ModPlug_Read(mod, single, modSettings.mChannels * (modSettings.mBits / 8)))
      for(int i = 0; i < modSettings.mChannels * (modSettings.mBits / 8); ++i)
        data.push_back(single[i]);
    
    ModPlug_Unload(mod);
    delete[] single;

    sf::SoundBuffer buffer;
    buffer.LoadFromSamples(reinterpret_cast<const sf::Int16*>(data.data()), data.size() / 2, modSettings.mChannels, modSettings.mFrequency);
    return buffer;
  }

}

#endif
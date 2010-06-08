#ifndef SLC_CONTENT_XMSOUND_H
#define SLC_CONTENT_XMSOUND_H

#include <cstring>
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
    modSettings.mBits = 16; // TODO: probably could do that at initialization-time
    ModPlug_SetSettings(&modSettings);

    ModPlugFile *mod = ModPlug_Load(filedata, filesize);
    //delete filedata; // appearently we do not delete this

    unsigned int rows, patternsSize = 0;
    for(unsigned int i = 0; i < ModPlug_NumPatterns(mod); ++i)
    {
      const ModPlugNote *notes = ModPlug_GetPattern(mod, i, &rows);
      /*for(unsigned int j = 0; j < rows; ++j)
      {
        std::cout << notes[j].Note << std::endl;
        if(notes[j].Note != 0)
          ++patternsSize;
      }*/
      patternsSize += rows;
    }

    int datasize = modSettings.mFrequency * patternsSize * /*ModPlug_NumChannels(mod) **/ modSettings.mChannels * (modSettings.mBits / 8);
    char *data = new char[datasize];
    
    std::cout << datasize << std::endl;
    
    datasize = ModPlug_Read(mod, data, datasize);
    
    ModPlug_Unload(mod);

    sf::SoundBuffer buffer;
    buffer.LoadFromSamples(reinterpret_cast<sf::Int16*>(data), datasize / 2, modSettings.mChannels, modSettings.mFrequency);
    //delete data; // appearently we do not delete this
    return buffer;
  }

}

#endif
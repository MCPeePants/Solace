#ifndef SLC_CONTENT_XMSOUND_H
#define SLC_CONTENT_XMSOUND_H

#include <string>

#include <SFML/Audio/SoundStream.hpp>

#include <libmodplug/modplug.h>

namespace sf{
  class SoundBuffer;
}

namespace content{

  extern bool openXMFile(const std::string &path, sf::SoundBuffer &buf);
  
  class XMStream : public sf::SoundStream
  {
  public:
    XMStream();
    ~XMStream();
    
    // note: violating convention
    bool Open(const std::string &path);
    
  private:
    bool OnGetData(Chunk& data);
    
    void OnSeek(float timeOffset){ ModPlug_Seek(mod, timeOffset * 1000);}
    
  private:
    ModPlugFile *mod;
    int singleSampleSize, samplesSize;
    char *samples;
  };

}

#endif
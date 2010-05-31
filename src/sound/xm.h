#ifndef SLC_SOUND_XM_H
#define SLC_SOUND_XM_H

#include "modplug.h"

namespace sound{

  class XmSound{

    private:
    signed short int* samples;
    int samp_sz;
    ModPlugFile * mpFile;

    public:
    XmSound() {}
    ~XmSound() {}

    struct Samples{
      signed short int* samples;
      int sz;
    };

    bool Load(const std::string& fileName);
    Samples GetSamples();

  };

}

#endif

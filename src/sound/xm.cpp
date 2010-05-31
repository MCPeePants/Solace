#include <fstream>
#include <string>

#include <sys/types.h>
#include <sys/stat.h>

#include "xm.h"

namespace sound{

  bool XmSound::Load(const std::string & fileName)
  {

    struct stat res;
    std::fstream input;
    char * buffer;

    if((stat(fileName.c_str(), &res) != 0))
      return false;

    samp_sz = res.st_size;
    buffer = new char[samp_sz + 1]; // + 1 just in case...

    input.open(fileName.c_str(), std::ios::in | std::ios::binary);
    if(!input.read(buffer, res.st_size))
      return false;

    mpFile = ModPlug_Load(buffer, res.st_size);
    samples = new signed short int[(samp_sz / 2) + 1]; // Total size should be the same as with the char buffer

    ModPlug_Read( mpFile, samples, samp_sz );

    return true;

  }

  XmSound::Samples XmSound::GetSamples()
  {
    Samples samp;

    samp.samples = samples;
    samp.sz = samp_sz;
  }

}

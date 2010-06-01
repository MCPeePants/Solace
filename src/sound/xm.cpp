#include <fstream>
#include <string>
#include <iostream>

#include <sys/types.h>
#include <sys/stat.h>

#include "xm.h"

namespace sound{

  bool XmSound::Load(const std::string & fileName)
  {

    struct stat res;
    std::fstream input;
    char * buffer;

    if((stat(fileName.c_str(), &res) != 0)){
      // std::cout << "SHIT FUCKED UP. "; // Debug messageeeees
      return false;
    }

    samp_sz = res.st_size;
    buffer = new char[samp_sz];

    input.open(fileName.c_str(), std::ios::in | std::ios::binary);
    if(!input.read(buffer, res.st_size)){
      // std::cout << "SHIT STILL FUCKED UP. ";
      return false;
    }

    mpFile = ModPlug_Load(buffer, res.st_size);
    samples = new signed short int[int((samp_sz / 2) + 0.5)]; // Total size should be the same as with the char buffer

    std::cout << ModPlug_Read( mpFile, samples, samp_sz );

    return true;

  }

  XmSound::Samples XmSound::GetSamples()
  {
    static Samples samp;

    samp.samples = samples;
    samp.sz = samp_sz;
  }

}

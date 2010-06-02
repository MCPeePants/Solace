#include <fstream>
#include <string>
#include <iostream>

#include <boost/filesystem.hpp>

#include "xm.h"

namespace sound{

  bool XmSound::Load(const std::string &fileName)
  {
    std::fstream input;
    char * buffer;

    if(!boost::filesystem::exists(fileName)){
      //std::cout << "SHIT FUCKED UP. "; // Debug messageeeees
      return false;
    }

    samp_sz = boost::filesystem::file_size(fileName);
    buffer = new char[samp_sz];

    input.open(fileName.c_str(), std::ios::in | std::ios::binary);
    if(!input.read(buffer, samp_sz)){
      // std::cout << "SHIT STILL FUCKED UP. ";
      return false;
    }

    mpFile = ModPlug_Load(buffer, samp_sz);
    samples = new signed short int[int((samp_sz / 2) + 0.5)]; // Total size should be the same as with the char buffer

    std::cout << ModPlug_Read( mpFile, samples, samp_sz );

    return true;

  }

  XmSound::Samples XmSound::GetSamples()
  {
    static Samples samp;

    samp.samples = samples;
    samp.sz = samp_sz;
    
    return samp;
  }

}

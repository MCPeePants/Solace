#ifndef SLC_CONTENT_RESOURCE_FWD_H
#define SLC_CONTENT_RESOURCE_FWD_H

namespace content{

enum LoaderError
{
  FILE_NOT_FOUND = 0,
  NON_RESOURCE_FILE,
  INVALID_DATA
};

}

#include "content/resource.h"

#endif
#ifndef SLC_LOGIC_SHIP_H
#define SLC_LOGIC_SHIP_H

#include "ObjDynamic.h"
#include "Ship_fwd.h"

namespace logic{

  class Ship: public ObjDynamic{

    public:
    virtual ~Ship() {} // In case this'll be a base class
 
    // TODO: Some smart way of listing modules and their stats? ;esa

    protected:

  };

}

#endif

#include "baseUI.h"

namespace graphics{ namespace ui{
    void ControlList::add(BaseControl control)
    {
        ControlList::controlList.push_back(&control);
    }
}}

#ifndef SLC_GRAPHICS_UI_BASE_H
#define SLC_GRAPHICS_UI_BASE_H

#include <list>

#include <SFML/Graphics.hpp>

#include "base_fwd.h"

class BaseControl
{
    friend class ControlList;

    private:
    virtual void draw(sf::RenderWindow& context) = 0;
};

class ControlList
{
    private:
    std::list<BaseControl*> controlList;

    public:
    void add(BaseControl* control);
};

#endif // SLC_GRAPHICS_UI_BASE_H

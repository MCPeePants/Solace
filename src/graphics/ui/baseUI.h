// BaseUI.h
// Provides the BaseClass for all controls to derive from
// as well as a list to store controls in

#ifndef SLC_GRAPHICS_UI_GUI_CONTROLS_H
#define SLC_GRAPHICS_UI_GUI_CONTROLS_H

#include <list>

#include <SFML/Graphics.hpp>

namespace graphics{ namespace ui{
    class BaseControl
    {
        public:
        virtual void Draw(sf::RenderWindow& Context) {};
    };

    class ControlList
    {
        private:
        std::list<BaseControl*> controlList;

        public:
        void add(BaseControl control);
    };
}}

#endif // SLC_GRAPHICS_UI_GUI_CONTROLS_H

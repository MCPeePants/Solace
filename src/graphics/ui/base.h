#ifndef SLC_GRAPHICS_UI_BASE_H
#define SLC_GRAPHICS_UI_BASE_H

#include <list>

#include <SFML/Graphics.hpp>

#include "base_fwd.h"

namespace graphics{ namespace ui{

class BaseControl
{
    friend class ControlList;

    private:
    virtual void draw(sf::RenderWindow& context) = 0;
    virtual void processInput(sf::Event& event) = 0;

    protected:
    float x, y, width, height;

    public:
    float getX();
    float getY();
	float getWidth();
	float getHeight();
	void setCoords(float tempX, float tempY);
    void setX(float tempX);
	void setY(float tempY);
	void setSize(float tempWidth, float tempHeight);
	void setWidth(float tempWidth);
	void setHeight(float tempHeight);
};

class ControlList
{
    private:
    std::list<BaseControl*> controls;

    public:
    void add(BaseControl& control);
};

}}

#endif // SLC_GRAPHICS_UI_BASE_H

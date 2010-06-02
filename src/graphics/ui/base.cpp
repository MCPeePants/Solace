#include "base.h"

namespace graphics{ namespace ui{

float BaseControl::getX()
{
    return x;
}
float BaseControl::getY()
{
    return y;
}
float BaseControl::getWidth()
{
    return width;
}
float BaseControl::getHeight()
{
    return height;
}
void BaseControl::setCoords(float tempX, float tempY)
{
    x = tempX;
    y = tempY;
}
void BaseControl::setX(float tempX)
{
    x = tempX;
}
void BaseControl::setY(float tempY)
{
    y = tempY;
}
void BaseControl::setSize(float tempWidth, float tempHeight)
{
    width = tempWidth;
    height = tempHeight;
}
void BaseControl::setWidth(float tempWidth)
{
    width = tempWidth;
}
void BaseControl::setHeight(float tempHeight)
{
    height = tempHeight;
}

}}

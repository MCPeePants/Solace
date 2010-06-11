#include "button.h"

namespace graphics{ namespace ui{

void Button::setText(std::string tempText)
{
	sf::Font font;
	font = sf::Font::GetDefaultFont();
	text.SetText(tempText);
	text.SetFont(font);
}

Button::Button(float tempX, float tempY, float tempWidth, float tempHeight, void (*buttonFunc)())
{
    x = tempX;
    y = tempY;
    width = tempWidth;
    height = tempHeight;

    buttonRect = sf::Shape::Rectangle(x, y, x+width, y+height, sf::Color(180,180,180), 1.0f, sf::Color(80,80,80));

    buttonCallback = buttonFunc;
}

void Button::draw(sf::RenderWindow& context)
{
    context.Draw(buttonRect);
}

void Button::processInput(sf::Event &event)
{
    switch(event.Type)
    {
        case(sf::Event::MouseButtonPressed):
            // Check if mouse is in bounds
            if(event.MouseButtonEvent.X > x &&
               event.MouseButtonEvent.Y > y &&
               event.MouseButtonEvent.X < x + width &&
               event.MouseButtonEvent.Y < y + height)
               buttonCallback();
            break;

        default:
            return;
    }
}

}}

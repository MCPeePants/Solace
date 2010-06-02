#include "button.h"

Button::setText(std::string tempText)
{
	sf::Font font;
	font.SetFont(sf::Font::GetDefaultFont());
	text.SetText(tempText);
	text.SetFont(font);
}
#ifndef SLC_GRAPHICS_UI_BUTTON_H
#define SLC_GRAPHICS_UI_BUTTON_H

#include "base.h"
#include "button_fwd.h"

namespace graphics{ namespace ui{
	class Button : BaseControl {
	private:
		virtual void draw(sf::RenderWindow& context);
		sf::String text;

	public:
		void setText(std::string tempText);
	};
}}
#endif // SLC_GRAPHICS_UI_BUTTON_H

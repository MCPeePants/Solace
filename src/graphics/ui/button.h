#ifndef SLC_GRAPHICS_UI_BUTTON_H
#define SLC_GRAPHICS_UI_BUTTON_H

#include "base.h"
#include "button_fwd.h"

namespace graphics{ namespace ui{
	class Button : BaseControl {
	private:
		void draw(sf::RenderWindow& context);

	public:
		void setText(std::string text);
	};
}}
#endif // SLC_GRAPHICS_UI_BUTTON_H

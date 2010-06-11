#ifndef SLC_GRAPHICS_UI_BUTTON_H
#define SLC_GRAPHICS_UI_BUTTON_H

#include "base.h"
#include "button_fwd.h"

namespace graphics{ namespace ui{
	class Button : BaseControl {
	private:
        // Stops the compiler whining
		virtual ~Button() {}
        // Draws the button to the drawing context
		virtual void draw(sf::RenderWindow& context);
		// Handles the mouse events
		virtual void processInput(sf::Event& event);

		// TEMPORARY!!! REPLACE THESE WITH STUFF FROM THE CONTENT LOADER!!!
		sf::Shape buttonRect;
		sf::String text;

		void (*buttonCallback)();

	public:
        Button(float tempX, float tempY, float tempWidth, float tempHeight, void (*buttonFunc)());
		void setText(std::string tempText);
	};
}}
#endif // SLC_GRAPHICS_UI_BUTTON_H

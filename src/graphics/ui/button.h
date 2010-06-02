#ifndef SLC_GRAPHICS_UI_BUTTON_H
#define SLC_GRAPHICS_UI_BUTTON_H
#include "base.h"

namespace graphics{ namespace ui{ // This is so damn ugly
	class Button : BaseControl {
	private:
		int x, y, width, height;
	public:
		int getX();
		int getY();
		int getWidth();
		int getHeight();
		void setCoords(int tempX, int tempY);
		void setX(intt tempX);
		void setY(int tempY);
		void setSize(int tempWidth, int tempHeight);
		void setWidth(int tempWidth);
		void setHeight(intt tempHeight);
		void setText(std::string text);
	};
}}
#endif // SLC_GRAPHICS_UI_BUTTON_H

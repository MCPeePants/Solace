#include "base.h"

namespace graphics{ namespace ui{ // This is so damn ugly
	class Button : BaseControl {
	private:
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
		void setText(std::string text);
	};
}}
#include "baseUI.h"

namespace graphics{ namespace ui{

    class Button : BaseControl
    {
        public:
        void Draw(sf::RenderWindow& Context)
        {
            sf::Shape rect = sf::Shape::Rectangle(10, 10, 20, 20, sf::Color(255,255,255));
            Context.Draw(rect);
        }
    };

}}

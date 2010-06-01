#include <iostream>
#include <SFML/Graphics.hpp>
<<<<<<< HEAD

=======
>>>>>>> e73104dfc677f40ff997e88e4c02072994331660
#include "graphics/ui/baseUI.h"
#include "graphics/ui/Button.h"

<<<<<<< HEAD
// Function declarations //
#include <iostream>

#include "../src/math/vector.h"
=======
>>>>>>> e73104dfc677f40ff997e88e4c02072994331660
/// Function declarations ///
void renderScene(sf::RenderWindow&);
void getEvents(sf::RenderWindow&);
/// ///

// Window width and height
int gameWidth = 1024;
int gameHeight = 768;

// Framerate cap
int maxFramerate = 60;

/// REMOVE ME
graphics::ui::Button btn;

int main()
{
    // Create a window to draw on
    sf::RenderWindow Wnd(sf::VideoMode(gameWidth, gameHeight), "Solace", sf::Style::Close);
    Wnd.SetFramerateLimit(maxFramerate);

    // CORE GAME LOOP //
    while(Wnd.IsOpened())
    {
        // Process window events
        getEvents(Wnd);
        // Render the game onto the current window
        renderScene(Wnd);
    }

    return 0;
}

<<<<<<< HEAD
<<<<<<< HEAD
// This function handles all of the game's drawing
// If possible, do ALL drawing code in here, not
// outside of it.
// ARGUMENTS:
//     *Surface => Pointer to the window to draw on
void renderScene(sf::RenderWindow *surface)
{
    surface->Clear();

    btn.Draw(surface);

    surface->Display();
=======
=======
>>>>>>> e73104dfc677f40ff997e88e4c02072994331660
/// This function handles all of the game's drawing
/// If possible, do ALL drawing code in here, not
/// outside of it.
/// ARGUMENTS:
///     &Surface => Reference of the context to draw on
void renderScene(sf::RenderWindow& surface)
{
    surface.Clear();
    surface.Display();
}

/// This function handles any Events/Inputs thrown to the game
/// Do any input code here
/// Arguments are window => Window to register inputs from
/// THANKS TO JA_COP FOR HELPING ME OUT WITH THIS :)
void getEvents(sf::RenderWindow& window)
{
	sf::Event event;
	while(window.GetEvent(event))
	{
		switch(event.Type)
		{
		case sf::Event::Closed:
			window.Close();
			break;

		case sf::Event::KeyPressed:
			if(event.Key.Code == sf::Key::Escape)
				window.Close();
			break;

		default:
			// I don't know what to do here but ja_cop says this:
			// Pass to input module or GUI module (placeholder)
			// so do that i guess
            // TODO: ADD MORE INPUTS
			break;
		}
	}
<<<<<<< HEAD
>>>>>>> 6dd25ae77c1bdb30fb11270916a668fd04e70d5b
=======
>>>>>>> e73104dfc677f40ff997e88e4c02072994331660
}

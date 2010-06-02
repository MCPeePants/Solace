#include <SFML/Graphics.hpp>

#include "graphics/ui/baseUI.h"

#include "graphics/ui/Button.h"

// Function declarations //
#include <iostream>

/// Function declarations ///
void renderScene(sf::RenderWindow&);
void getEvents(sf::RenderWindow&);
/// ///

int main()
{
    int gameWidth, gameHeight;
    int maxFramerate;
    {
        config::Config conf("config.lua");
        gameWidth = conf["width"].integer();
        gameHeight = conf["height"].integer();
        maxFramerate = conf["framerate"].integer();
    }

    // Create a window to draw on
    sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Solace", sf::Style::Close);
    window.SetFramerateLimit(maxFramerate);

    // CORE GAME LOOP //
    while(window.IsOpened())
    {
        // Process window events
        getEvents(window);
        // Render the game onto the current window
        renderScene(window);
    }

    return 0;
}

/// This function handles all of the game's drawing
/// If possible, do ALL drawing code in here, not
/// outside of it.
/// ARGUMENTS:
///     *Surface => Reference of the context to draw on
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
}

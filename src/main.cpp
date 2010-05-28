#include <SFML/Graphics.hpp>

/// Function declarations ///
void renderScene(sf::RenderWindow*);
/// ///

// Window width and height
int gameWidth = 1024;
int gameHeight = 768;

// Framerate cap
int maxFramerate = 60;

int main()
{
    // Create a window to draw on
    sf::RenderWindow Wnd(sf::VideoMode(gameWidth, gameHeight), "Solace", sf::Style::Close);
    Wnd.SetFramerateLimit(maxFramerate);

    /// CORE GAME LOOP ///
    while(Wnd.IsOpened())
    {
        // Process window events
        sf::Event event;
        while(Wnd.GetEvent(event))
        {
            if(event.Type == sf::Event::Closed)
                Wnd.Close();
        }

        // Render the game onto the current window
        renderScene(&Wnd);
    }

    return 0;
}

/// This function handles all of the game's drawing
/// If possible, do ALL drawing code in here, not
/// outside of it.
/// ARGUMENTS:
///     *Surface => Pointer to the window to draw on
void renderScene(sf::RenderWindow *surface)
{
    surface->Clear();
    surface->Display();
}

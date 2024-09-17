#include "Window.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Brick.hpp"
#include "Cannon.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 900), "Breakout");                      // Create a window with SFML

    bool quit = false;
    sf::Event event;

    Brick brick = Brick( 100, 100, 100, 100, "../assets/images/brick.png", 100);         // Create a brick object
    Cannon cannon = Cannon( 300, 800, 100, 200, "../assets/images/cannon.png");       // Create a cannon object


    while (window.isOpen()) {                                                           // Main game loop
        window.clear(sf::Color(251, 248, 239, 255));                                    // Clear the window     
        brick.render(window);                                                                 // Render the brick object
        cannon.render(window);                                                                // Render the cannon object
        cannon.updateRotation(window);                                                  // Update the cannon rotation

        window.display();                                                               // Display the window

        while (window.pollEvent(event)) {                                               // Poll events from the window to handle input          
            if (event.type == sf::Event::Closed) {                                      // Close the window if the close button is clicked
                window.close();
                quit = true;
            }
        }
    }
    return 0;
}
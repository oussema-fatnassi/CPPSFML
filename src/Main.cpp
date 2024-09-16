#include "Window.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 900), "Breakout");                      // Create a window with SFML

    bool quit = false;
    sf::Event event;


    while (window.isOpen()) {                                                           // Main game loop
        window.clear(sf::Color(251, 248, 239, 255));                                    // Clear the window     

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
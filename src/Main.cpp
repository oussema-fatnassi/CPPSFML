#include "Window.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Brick.hpp"
#include "Cannon.hpp"
#include "MathHelper.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 900), "Breakout"); // Create a window with SFML

    bool quit = false;
    sf::Event event;
    MathHelper mathHelper;

    Brick brick = Brick(sf::Vector2f(100, 100), sf::Vector2f(50, 50), "../assets/images/Diamond.png", 100); // Create a brick object
    Brick brick1 = Brick(sf::Vector2f(150, 100), sf::Vector2f(50, 50), "../assets/images/Obsidian.png", 100); // Create a brick object
    Brick brick2 = Brick(sf::Vector2f(200, 100), sf::Vector2f(50, 50), "../assets/images/Dirt.png", 100); // Create a brick object
    Brick brick3 = Brick(sf::Vector2f(250, 100), sf::Vector2f(50, 50), "../assets/images/GoldOre.png", 100); // Create a brick object
    Brick brick4 = Brick(sf::Vector2f(300, 100), sf::Vector2f(50, 50), "../assets/images/RubyOre.png", 100); // Create a brick object
    Brick brick5 = Brick(sf::Vector2f(350, 100), sf::Vector2f(50, 50), "../assets/images/Stone.png", 100); // Create a brick object
    Brick brick6 = Brick(sf::Vector2f(400, 100), sf::Vector2f(50, 50), "../assets/images/TNT.png", 100); // Create a brick object


    std::vector<Brick> bricks = {brick, brick1, brick2, brick3, brick4, brick5, brick6}; // Create a vector of bricks

    Cannon cannon = Cannon(sf::Vector2f (300, 800),sf::Vector2f (100, 200), "../assets/images/cannon.png"); // Create a cannon object

    while (window.isOpen()) { // Main game loop
        window.clear(sf::Color(251, 248, 239, 255)); // Clear the window

        // Render the objects
       for (auto& brick : bricks) {
            brick.render(window);
        }
        cannon.render(window);
        // Draw the trajectory line and get the vertex array
        cannon.drawTrajectory(window);


        // Update the cannon rotation
        cannon.updateRotation(window);

        window.display(); // Display the window

        while (window.pollEvent(event)) { // Poll events from the window to handle input
            if (event.type == sf::Event::Closed) { // Close the window if the close button is clicked
                window.close();
                quit = true;
            }
        }
    }

    return 0;
}

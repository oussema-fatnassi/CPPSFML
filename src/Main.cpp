#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>              // Include vector for storing bullets
#include "MathHelper.hpp"      // Include MathHelper header
#include "Brick.hpp"           // Include Brick header
#include "Cannon.hpp"          // Include Cannon header
#include "Bullet.hpp"          // Include Bullet header

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 900), "Breakout"); // Create a window with SFML

    bool quit = false;
    sf::Event event;
    MathHelper mathHelper;  // Corrected declaration of MathHelper

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

        // Update the cannon rotation
        cannon.updateRotation(window);

        window.display(); // Display the window

        // Event handling
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                quit = true;
            }

            // Handle right-click to shoot
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                bullets.push_back(cannon.shoot());  // Add a new bullet when right-clicked
            }
        }
    }

    return 0;
}

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

    // Create brick objects
    Brick brick = Brick(sf::Vector2f(100, 100), sf::Vector2f(50, 50), "../assets/images/Diamond.png", 100); // Create a brick object
    Brick brick1 = Brick(sf::Vector2f(150, 100), sf::Vector2f(50, 50), "../assets/images/Obsidian.png", 100); // Create a brick object
    Brick brick2 = Brick(sf::Vector2f(200, 100), sf::Vector2f(50, 50), "../assets/images/Dirt.png", 100); //

    // Create a vector of bricks
    std::vector<Brick> bricks = {brick, brick1, brick2};

    // Create a cannon object
    Cannon cannon = Cannon(sf::Vector2f (300, 900),sf::Vector2f (100, 200), "../assets/images/cannon.png"); // Create a cannon object

    std::vector<Bullet> bullets; // Vector to store bullets

    while (window.isOpen()) { // Main game loop
        window.clear(sf::Color(251, 248, 239, 255)); // Clear the window

        // Draw the trajectory line and get the vertex array
        cannon.drawTrajectory(window);

        // Update the cannon rotation
        cannon.updateRotation(window);

        // Render the objects
        for (auto& brick : bricks) {
            brick.render(window);
        }
        cannon.render(window);

        // Update and render bullets
        for (auto it = bullets.begin(); it != bullets.end(); ) {
            it->update(cannon.getPosition());  // Update bullet
            if (!it->isActive()) {             // Check if bullet is inactive
                it = bullets.erase(it);        // Remove inactive bullet from the vector
            } else {
                it->render(window);            // Render active bullet
                ++it;                          // Move to the next bullet
            }
        }

        window.display();  // Display the window
        cout << "Number of bullets: " << bullets.size() << endl;  // Print the number of bullets

        // Event handling
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                quit = true;
            }

            // Handle right-click to shoot
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right && bullets.size() == 0) {
                bullets.push_back(cannon.shoot());  // Add a new bullet when right-clicked
            }
        }
    }

    return 0;
}
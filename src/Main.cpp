#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>              // Include vector for storing bullets
#include "MathHelper.hpp"      // Include MathHelper header
#include "Brick.hpp"           // Include Brick header
#include "Cannon.hpp"          // Include Cannon header
#include "Bullet.hpp"          // Include Bullet header
#include "LoadFromFile.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 900), "Breakout"); // Create a window with SFML

    bool quit = false;
    sf::Event event;
    MathHelper mathHelper;  // Corrected declaration of MathHelper
    LoadFromFile loadFromFile("../assets/map/matrix.txt");  // Load the matrix file
    loadFromFile.loadGrid();  // Load the grid
    loadFromFile.printGrid(); // Optional: print the grid to verify

    vector<Brick> bricks = loadFromFile.createBricks();  // Create bricks from the matrix file
    Cannon cannon = Cannon(sf::Vector2f (300, 900), sf::Vector2f (100, 200), "../assets/images/cannon.png"); // Create a cannon object
    std::vector<Bullet> bullets; // Vector to store bullets

    while (window.isOpen()) { // Main game loop
        window.clear(sf::Color(251, 248, 239, 255)); // Clear the window

        cannon.drawTrajectory(window);
        cannon.updateRotation(window);

        // Update and render bricks
        for (auto& brick : bricks) {
            brick.render(window);
        }
        cannon.render(window);

        // Update and render bullets
        for (auto it = bullets.begin(); it != bullets.end(); ) {
            it->update(cannon.getPosition(), bricks);  // Update bullet and check for collisions with bricks
            if (!it->isActive()) {             // Check if bullet is inactive
                it = bullets.erase(it);        // Remove inactive bullet from the vector
            } else {
                it->render(window);            // Render active bullet
                ++it;                          // Move to the next bullet
            }
        }

        window.display();  // Display the window

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

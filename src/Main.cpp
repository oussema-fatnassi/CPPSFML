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

    // Create brick objects
    Brick brick(sf::Vector2f(100,100), sf::Vector2f(100,100), "../assets/images/brick.png", 100); 
    Brick brick2(sf::Vector2f(200,200), sf::Vector2f(100,100), "../assets/images/brick.png", 100); 

    // Create a vector of bricks
    std::vector<Brick> bricks = {brick, brick2};

    // Create a cannon object
    Cannon cannon(sf::Vector2f(300,800), sf::Vector2f(100,200), "../assets/images/cannon.png"); 

    std::vector<Bullet> bullets; // Vector to store bullets

    while (window.isOpen()) { // Main game loop
        window.clear(sf::Color(251, 248, 239, 255)); // Clear the window

        // Draw the trajectory line and get the vertex array
        // sf::VertexArray trajectoryLine = cannon.drawTrajectory(window);

        // Iterate through all the bric

        // Update the cannon rotation
        cannon.updateRotation(window);

        // Render the objects
        for (auto& brick : bricks) {
            brick.render(window);
        }
        cannon.render(window);

        // Update and render bullets
        for (auto& bullet : bullets) {
            bullet.update(cannon.getPosition());  // Pass the cannon's position to the update method
            bullet.render(window);  // Render the bullet
        }

        window.display();  // Display the window

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

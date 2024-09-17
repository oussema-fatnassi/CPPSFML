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

    Brick brick = Brick(100, 100, 100, 100, "../assets/images/brick.png", 100); // Create a brick object
    Brick brick2 = Brick(200, 200, 100, 100, "../assets/images/brick.png", 100); // Create a brick object

    std::vector<Brick> bricks = {brick, brick2};

    Cannon cannon = Cannon(300, 800, 100, 200, "../assets/images/cannon.png"); // Create a cannon object

    while (window.isOpen()) { // Main game loop
        window.clear(sf::Color(251, 248, 239, 255)); // Clear the window

        // Draw the trajectory line and get the vertex array
        sf::VertexArray trajectoryLine = cannon.drawTrajectory(window);

        // Iterate through all the bricks
        for (auto& brick : bricks) {
            // Check if the brick intersects with any of the lines in the trajectory line vertex array
            for (size_t i = 0; i < trajectoryLine.getVertexCount() - 1; i++) {
                sf::Vector2f lineStart = trajectoryLine[i].position;
                sf::Vector2f lineEnd = trajectoryLine[i + 1].position;

                if (mathHelper.lineIntersectsRectangle(lineStart, lineEnd, brick.getBounds())) {
                    // Collision detected, handle it here
                    // ...
                    std::cout << "Collision detected!" << std::endl;
                    cout << "Brick position: " << brick.getBounds().left << ", " << brick.getBounds().top << endl;

                    // Break the inner loop if a collision is detected
                    break;
                }
            }
        }

        // Render the objects
       for (auto& brick : bricks) {
            brick.render(window);
        }
        cannon.render(window);

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

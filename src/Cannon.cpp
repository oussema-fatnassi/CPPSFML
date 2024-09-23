#include "Cannon.hpp"

/*
Class definition for Cannon, a class that represents the cannon in the game.
*/

Cannon::Cannon(sf::Vector2f position, sf::Vector2f dimension, const string& imagePath,  SoundManager* soundManager)
    : GameObject(position, dimension, imagePath), soundManager(soundManager) {
    loadTexture(imagePath);
    sprite.setOrigin(dimension.x / 2.f, dimension.y /1.23f); 
    sprite.setRotation(rotation);
}

// Render the cannon
void Cannon::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

// Update the rotation of the cannon based on the mouse position
void Cannon::updateRotation(sf::RenderWindow& window) {
    sf::Vector2i mousePos = InputManager::getInstance().getMousePosition(window);
    sf::Vector2f cannonPos = sprite.getPosition();

    // Check if the mouse is above the cannon
    if (mousePos.y < cannonPos.y) {
        // Mouse is above the cannon, calculate the rotation angle
        float angle = MathHelper::getAngle(cannonPos.x, cannonPos.y, mousePos.x, mousePos.y);

        // Adjust the angle for the initial orientation of the cannon
        angle += 180.0f;

        // Set the new rotation
        setRotation(angle);
    }
    // If the mouse is below the cannon, do nothing (rotation remains unchanged)
}

// Set the rotation of the cannon
void Cannon::setRotation(float rotation) {
    this->rotation = rotation;
    sprite.setRotation(rotation);
}

// Get the rotation of the cannon
float Cannon::getRotation() const {
    return rotation;
}

// Draw the trajectory of the cannonball
void Cannon::drawTrajectory(sf::RenderWindow& window) {
    sf::Vector2f cannonPos = sprite.getPosition();
    float angle = getRotation();
    float radians = (angle - 90.f) * 3.14159265f / 180.0f;
    sf::Vector2f direction(std::cos(radians), std::sin(radians));
    float brickTopY = 580.0f;
    trajectoryManager.updateTrajectory(cannonPos, direction, window, brickTopY);    
}

// Calculate the end point of the trajectory line
float Cannon::calculateLineEnd(sf::Vector2f& lineEnd, const sf::Vector2f& direction, const sf::Vector2u& windowSize) {
    float t_max_x, t_max_y;

    if (direction.x != 0) {
        t_max_x = (direction.x > 0) ? (windowSize.x - lineEnd.x) / direction.x : (-lineEnd.x) / direction.x;
    } else {
        t_max_x = std::numeric_limits<float>::max(); // No movement in x direction
    }

    if (direction.y != 0) {
        t_max_y = (direction.y > 0) ? (windowSize.y - lineEnd.y) / direction.y : (-lineEnd.y) / direction.y;
    } else {
        t_max_y = std::numeric_limits<float>::max(); // No movement in y direction
    }

    // Use the smaller t_max value to find the intersection point
    float t_min = std::min(t_max_x, t_max_y);
    lineEnd = lineEnd + direction * t_min;

    return t_min;
}

// Determine the normal vector of the border hit
sf::Vector2f Cannon::determineBorderNormal(const sf::Vector2f& lineEnd, const sf::Vector2u& windowSize) {
    if (lineEnd.x <= 0) {
        return sf::Vector2f(1, 0); // Left border
    } else if (lineEnd.x >= windowSize.x) {
        return sf::Vector2f(-1, 0); // Right border
    } else if (lineEnd.y <= 0) {
        return sf::Vector2f(0, 1); // Top border
    } else if (lineEnd.y >= windowSize.y) {
        return sf::Vector2f(0, -1); // Bottom border, used to stop the trajectory
    }
    return sf::Vector2f(0, 0); // No border hit
}

// Reflect the direction vector around the normal vector
sf::Vector2f Cannon::reflectDirection(const sf::Vector2f& direction, const sf::Vector2f& normal) {
    // Reflect the direction vector around the normal
    float dotProduct = MathHelper::dotProduct(direction, normal);
    return direction - 2 * dotProduct * normal;
}

// Shoot a bullet from the cannon
Bullet Cannon::shoot() {
    // Set bullet properties: position, rotation, speed, damage
    int bulletWidth = 20;  // Set appropriate width
    int bulletHeight = 20; // Set appropriate height
    sf::Vector2f bulletDimension(bulletWidth, bulletHeight);
    float bulletSpeed = .6f; // Adjust the speed as needed
    int bulletDamage = 1; // Set damage amount

    // Get the cannon's current position and rotation
    sf::Vector2f cannonPosition = sprite.getPosition();
    float angle = sprite.getRotation();

    // Calculate the bullet's initial position at the top of the cannon
    float radians = (angle - 90.f) * 3.14159265f / 180.0f;
    sf::Vector2f bulletPosition = cannonPosition - sf::Vector2f(6.f, 1.f) + sf::Vector2f(std::cos(radians) * (sprite.getOrigin().y ), 
                                                                std::sin(radians) * (sprite.getOrigin().y ));

    // Create a bullet with the correct rotation
    Bullet bullet(sf::Vector2f(bulletPosition), sf::Vector2f(bulletDimension), "../assets/images/Ball.png", angle, bulletSpeed, bulletDamage);
    soundManager->playSound("crossbow"); 
    return bullet;
}

// Get the position of the cannon
sf::Vector2f Cannon::getPosition() const {
    return sprite.getPosition();
}
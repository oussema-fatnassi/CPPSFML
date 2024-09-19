#include "Bullet.hpp"
#include "MathHelper.hpp"
#include <cmath>

// Constructor definition
Bullet::Bullet(sf::Vector2f position, sf::Vector2f dimension, const string& imagePath, float rotation, float speed, int damage)
    : GameObject(position, dimension, imagePath), rotation(rotation), speed(speed), damage(damage), active(true) {
    loadTexture(imagePath);  // Load the texture for the bullet
    sprite.setRotation(rotation);  // Set the initial rotation
    sprite.setOrigin(dimension.x / 2.f, dimension.y / 2.f);  // Set the origin to the center of the bullet
    sprite.setPosition(position);  // Set the initial position of the bullet
    // Set the initial velocity based on the given rotation angle
    float radians = (rotation - 90.f) * 3.14159265f / 180.0f;
    velocity = sf::Vector2f(std::cos(radians), std::sin(radians)) * speed;
}

// Destructor definition
Bullet::~Bullet() {
    // Destructor logic if needed, otherwise it can be empty
}

// Update method
void Bullet::update(const sf::Vector2f& cannonPosition) {
    // Get the bullet's current position and window size
    sf::Vector2f bulletPos = sprite.getPosition();
    sf::FloatRect bulletBounds = sprite.getGlobalBounds();  // Global bounds of the bullet (x, y, width, height)
    sf::Vector2u windowSize(600, 900);  // Assuming a static window size for this example

    // Calculate the top-left and top-right positions of the bullet
    sf::Vector2f topLeft(bulletBounds.left, bulletBounds.top);  // Top-left corner
    sf::Vector2f topRight(bulletBounds.left + bulletBounds.width, bulletBounds.top);  // Top-right corner

    // Detect collisions with the window's left boundary
    if (topLeft.x <= 0) {
        // Invert the x-direction (horizontal bounce)
        velocity.x = -velocity.x;
    }
    // Detect collisions with the window's right boundary
    else if (topRight.x >= windowSize.x) {
        // Invert the x-direction (horizontal bounce)
        velocity.x = -velocity.x;
    }

    // Detect collisions with the window's top boundary
    if (topLeft.y <= 0) {
        // Invert the y-direction (vertical bounce)
        velocity.y = -velocity.y;
    }

    // Move the bullet using its velocity vector
    sprite.move(velocity);

    // Calculate the distance between the bullet and the cannon
    float distanceToCannon = std::sqrt(std::pow(bulletPos.x - cannonPosition.x, 2) + std::pow(bulletPos.y - cannonPosition.y, 2));

    // Deactivate bullet if it is near the cannon or hits the ground
    float groundLevel = 850.0f;  // Define the ground level (bottom of the screen)
    if (distanceToCannon < 50.0f || bulletPos.y >= groundLevel) {
        deactivate();  // Deactivate the bullet
    }
}


// Render method
void Bullet::render(sf::RenderWindow& window) {
    if (active) {
        window.draw(sprite);  // Draw the bullet sprite to the window only if it's active
    }
}

// Deactivate the bullet
void Bullet::deactivate() {
    active = false;
}

// Check if the bullet is active
bool Bullet::isActive() const {
    return active;
}
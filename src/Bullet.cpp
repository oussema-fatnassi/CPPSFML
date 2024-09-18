#include "Bullet.hpp"
#include "MathHelper.hpp"
#include <cmath>

// Constructor definition
Bullet::Bullet(int x, int y, int width, int height, const std::string& imagePath, float rotation, float speed, int damage)
    : GameObject(x, y, width, height, imagePath), rotation(rotation), speed(speed), damage(damage), active(true) {
    loadTexture(imagePath);  // Load the texture for the bullet
    sprite.setRotation(rotation);  // Set the initial rotation
}

// Destructor definition
Bullet::~Bullet() {
    // Destructor logic if needed, otherwise it can be empty
}

// Update method
void Bullet::update(const sf::Vector2f& cannonPosition) {
    // Convert the rotation angle from degrees to radians
    float radians = (rotation - 90.f) * 3.14159265f / 180.0f;

    // Calculate the current movement direction based on the rotation angle
    sf::Vector2f direction(std::cos(radians), std::sin(radians));

    // Get the bullet's current position and window size
    sf::Vector2f bulletPos = sprite.getPosition();
    sf::FloatRect bulletBounds = sprite.getGlobalBounds();
    sf::Vector2u windowSize(600, 900);  // Assuming a static window size for this example

    // Detect collisions with the window's left or right boundary
    if (bulletPos.x <= 0 || bulletPos.x + bulletBounds.width >= windowSize.x) {
        sf::Vector2f normal(1.f, 0.f);  // Normal vector for vertical boundaries (left/right)
        direction = MathHelper::reflectDirection(direction, normal);  // Reflect the direction on the x-axis
    }

    // Detect collisions with the window's top or bottom boundary
    if (bulletPos.y <= 0) {
        sf::Vector2f normal(0.f, 1.f);  // Normal vector for horizontal boundaries (top/bottom)
        direction = MathHelper::reflectDirection(direction, normal);  // Reflect the direction on the y-axis
    }

    // Move the bullet in the new direction
    sprite.move(direction * speed);

    // Update the bullet's rotation to reflect the new movement direction
    rotation = atan2(direction.y, direction.x) * 180.f / 3.14159265f + 90.f;
    sprite.setRotation(rotation);

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
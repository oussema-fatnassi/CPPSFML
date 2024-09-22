#include "Bullet.hpp"
#include "MathHelper.hpp"

/*
Class definition for Bullet, a class that represents a bullet in the game.
*/

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
void Bullet::update(const sf::Vector2f& cannonPosition, std::vector<Brick>& bricks, std::vector<Image>& walls) {
    // Move the bullet using its velocity vector
    sprite.move(velocity);

    // Check for collisions with bricks
    handleBrickCollision(bricks);

    // Check for collisions with the wall images
    for (auto& wall : walls) {
        if (sprite.getGlobalBounds().intersects(wall.getGlobalBounds())) {
            sf::FloatRect bulletBounds = sprite.getGlobalBounds();
            sf::FloatRect wallBounds = wall.getGlobalBounds();

            float bulletCenterX = bulletBounds.left + bulletBounds.width / 2.f;
            float bulletCenterY = bulletBounds.top + bulletBounds.height / 2.f;
            float wallCenterX = wallBounds.left + wallBounds.width / 2.f;
            float wallCenterY = wallBounds.top + wallBounds.height / 2.f;

            float dx = bulletCenterX - wallCenterX;
            float dy = bulletCenterY - wallCenterY;

            if (std::abs(dx) > std::abs(dy)) {
                velocity.x = -velocity.x;  // Reflect horizontally
            } else {
                velocity.y = -velocity.y;  // Reflect vertically
            }

            break;  // Only handle one collision at a time
        }
    }

    // Deactivate bullet if it is near the cannon or hits the ground
    float groundLevel = 825.0f;  // Define the ground level (bottom of the screen)
    if (sprite.getPosition().y >= groundLevel) {
        deactivate();  // Deactivate the bullet
    }
}


// Handle collision with bricks
void Bullet::handleBrickCollision(std::vector<Brick>& bricks) {
    bool hasCollided = false;
    for (auto it = bricks.begin(); it != bricks.end() && !hasCollided; ) {
        if (sprite.getGlobalBounds().intersects(it->getGlobalBounds())) {
            sf::FloatRect bulletBounds = sprite.getGlobalBounds();
            sf::FloatRect brickBounds = it->getGlobalBounds();

            float bulletCenterX = bulletBounds.left + bulletBounds.width / 2.f;
            float bulletCenterY = bulletBounds.top + bulletBounds.height / 2.f;
            float brickCenterX = brickBounds.left + brickBounds.width / 2.f;
            float brickCenterY = brickBounds.top + brickBounds.height / 2.f;

            float dx = bulletCenterX - brickCenterX;
            float dy = bulletCenterY - brickCenterY;

            if (std::abs(dx) > std::abs(dy)) {
                velocity.x = -velocity.x;
            } else {
                velocity.y = -velocity.y;
            }

            // Reduce the brick's health by the bullet's damage
            it->reduceHealth(damage);

            // If the brick is destroyed, remove it
            if (it->isDestroyed()) {
                it = bricks.erase(it);
            } else {
                ++it;  // Move to the next brick if not destroyed
            }

            hasCollided = true;  // Only handle one collision per frame
        } else {
            ++it;
        }
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
#include "Brick.hpp"

Brick::Brick(sf::Vector2f position, sf::Vector2f dimension, const string& imagePath, int health) 
    : GameObject(position,dimension, imagePath), health(health) {
    loadTexture(imagePath);
}

void Brick::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

int Brick::getHealth() const {
    return health;
}

void Brick::reduceHealth(int damage) {
    health -= damage;
}

bool Brick::isDestroyed() const {
    return health <= 0;
}

sf::FloatRect Brick::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

sf::Vector2f Brick::getNormal(const sf::Vector2f& collisionPoint) const {
    sf::FloatRect bounds = getGlobalBounds();

    // Calculate distances to each side
    float distanceToLeft = collisionPoint.x - bounds.left;
    float distanceToRight = bounds.left + bounds.width - collisionPoint.x;
    float distanceToTop = collisionPoint.y - bounds.top;
    float distanceToBottom = bounds.top + bounds.height - collisionPoint.y;

    // Find the smallest distance
    float minDistance = std::min({distanceToLeft, distanceToRight, distanceToTop, distanceToBottom});

    // Return the normal vector of the closest side
    if (minDistance == distanceToLeft) {
        return sf::Vector2f(-1.f, 0.f); // Left side
    } else if (minDistance == distanceToRight) {
        return sf::Vector2f(1.f, 0.f);  // Right side
    } else if (minDistance == distanceToTop) {
        return sf::Vector2f(0.f, -1.f); // Top side
    } else {
        return sf::Vector2f(0.f, 1.f);  // Bottom side
    }
}

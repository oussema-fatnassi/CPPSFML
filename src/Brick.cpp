#include "Brick.hpp"

/*
Class definition for Brick, a class that represents a brick in the game.
*/

Brick::Brick(sf::Vector2f position, sf::Vector2f dimension, const string& imagePath, int health, SoundManager* soundManager) 
    : GameObject(position,dimension, imagePath), health(health), maxHealth(health), texturePath(imagePath), soundManager(soundManager) {
    loadTexture(imagePath);
}

// Render the brick
void Brick::render(sf::RenderWindow& window) {
    window.draw(sprite);
}
// Get the health of the brick
int Brick::getHealth() const {
    return health;
}

// Reduce the health of the brick by the given damage amount
void Brick::reduceHealth(int damage) {
    health -= damage;

    // Determine which crack sound to play based on maxHealth
    std::string crackSound = (maxHealth >= 5) ? "ore-crack" : "brick-crack";

    // Change texture to cracked if health is at half or below
    if (health <= maxHealth / 2 && maxHealth > 1 && !isCracked) { // Check if it's not cracked yet
        string crackedTexturePath = getCrackedTexturePath();
        loadTexture(crackedTexturePath);
        soundManager->playSound(crackSound); // Play the appropriate crack sound
        isCracked = true; // Set the flag to true
    }

    // Check if the brick is destroyed
    if (isDestroyed()) {
        soundManager->playSound(crackSound); // Play the appropriate destroy sound
    }
}


// Check if the brick is destroyed
bool Brick::isDestroyed() const {
    return health <= 0;
}

// Get the global bounds of the brick
sf::FloatRect Brick::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

// Get the normal vector of the brick at the given collision point
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

// Get the path to the cracked texture
string Brick::getCrackedTexturePath() const {
    size_t lastDot = texturePath.find_last_of(".");
    if (lastDot != string::npos) {
        return texturePath.substr(0, lastDot) + "-cracked" + texturePath.substr(lastDot);
    }
    return texturePath + "-cracked"; // Fallback if no dot found
}

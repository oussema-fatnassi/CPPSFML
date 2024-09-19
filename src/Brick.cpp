#include "Brick.hpp"

Brick::Brick(sf::Vector2f(position), sf::Vector2f(dimension), const string& imagePath, int health) 
    : GameObject(position, dimension, imagePath), health(health) {
    loadTexture(imagePath);
}

void Brick::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

int Brick::getHealth() const {
    return health;
}

sf::FloatRect Brick::getBounds() const {
    return sprite.getGlobalBounds();
}
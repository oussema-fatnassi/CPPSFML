#include "Brick.hpp"

Brick::Brick(sf::RenderWindow& window, int x, int y, int width, int height, const string& imagePath, int health) 
    : GameObject(window, x, y, width, height, imagePath), health(health) {
    loadTexture(imagePath);
}

void Brick::render() {
    window.draw(sprite);
}
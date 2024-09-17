#include "Brick.hpp"

Brick::Brick(int x, int y, int width, int height, const string& imagePath, int health) 
    : GameObject(x, y, width, height, imagePath), health(health) {
    loadTexture(imagePath);
}

void Brick::render(sf::RenderWindow& window) {
    window.draw(sprite);
}
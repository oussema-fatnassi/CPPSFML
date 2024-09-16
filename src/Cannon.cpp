#include "Cannon.hpp"

Cannon::Cannon(sf::RenderWindow& window, int x, int y, int width, int height, const string& imagePath, float rotation) 
    : GameObject(window, x, y, width, height, imagePath), rotation(rotation) {
    loadTexture(imagePath);
    sprite.setRotation(rotation);
}

void Cannon::render() {
    window.draw(sprite);
}

void Cannon::setRotation(float rotation) {
    this->rotation = rotation;
    sprite.setRotation(rotation);
}

float Cannon::getRotation() const {
    return rotation;
}
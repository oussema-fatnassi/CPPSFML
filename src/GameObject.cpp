#include "GameObject.hpp"

GameObject::GameObject(sf::RenderWindow& window, int x, int y, int width, int height, const string& imagePath) : window(window), x(x), y(y), width(width), height(height) {
    loadTexture(imagePath);
    sprite.setTexture(*texture);
    sprite.setPosition(x, y);
}

void GameObject::loadTexture(const string& imagePath) {
    texture = AssetManager::getInstance().getTexture(imagePath);
    sprite.setTexture(*texture);
    sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
    sprite.setScale(
        static_cast<float>(width) / texture->getSize().x,
        static_cast<float>(height) / texture->getSize().y
    );
}

void GameObject::setTexture(const string& imagePath) {
    loadTexture(imagePath);
}

int GameObject::getX() const {
    return x;
}

int GameObject::getY() const {
    return y;
}

int GameObject::getWidth() const {
    return width;
}

int GameObject::getHeight() const {
    return height;
}

void GameObject::render() {
    window.draw(sprite);
}
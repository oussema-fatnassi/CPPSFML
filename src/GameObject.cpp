#include "GameObject.hpp"

GameObject::GameObject(sf::Vector2f position, sf::Vector2f dimension, const string& imagePath) 
    : position(position), dimension(dimension) {
    loadTexture(imagePath);
    sprite.setTexture(*texture);
    sprite.setPosition(position);
}

void GameObject::loadTexture(const string& imagePath) {
    texture = AssetManager::getInstance().getTexture(imagePath);
    sprite.setTexture(*texture);
    sprite.setPosition(position);
    sprite.setScale(
        dimension.x / texture->getSize().x,
        dimension.y / texture->getSize().y
    );
}

void GameObject::setTexture(const string& imagePath) {
    loadTexture(imagePath);
}

void GameObject::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::Vector2f GameObject::getPosition() const {
    return position;
}

sf::Vector2f GameObject::getDimension() const {
    return dimension;
}



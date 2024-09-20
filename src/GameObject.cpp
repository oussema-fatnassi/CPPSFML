#include "GameObject.hpp"

/*
Class definition for GameObject, a base class for game objects.
*/

GameObject::GameObject(sf::Vector2f position, sf::Vector2f dimension, const string& imagePath) 
    : position(position), dimension(dimension) {
    loadTexture(imagePath);
    sprite.setTexture(*texture);
    sprite.setPosition(position);
}

// Load the texture of the game object
void GameObject::loadTexture(const string& imagePath) {
    texture = AssetManager::getInstance().getTexture(imagePath);
    sprite.setTexture(*texture);
    sprite.setPosition(position);
    sprite.setScale(
        dimension.x / texture->getSize().x,
        dimension.y / texture->getSize().y
    );
}

// Set the texture of the game object
void GameObject::setTexture(const string& imagePath) {
    loadTexture(imagePath);
}

// Render the game object
void GameObject::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

// Get the position of the game object
sf::Vector2f GameObject::getPosition() const {
    return position;
}

// Get the dimension of the game object
sf::Vector2f GameObject::getDimension() const {
    return dimension;
}

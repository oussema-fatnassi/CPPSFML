#include "Image.hpp"

/*
Image class is a derived class from GameObject. It is used to render images on the screen.
*/

Image::Image(sf::Vector2f position, sf::Vector2f dimension, const std::string& imagePath)
    : GameObject(position, dimension, imagePath) {
}

// Render the image using the inherited render method
void Image::render(sf::RenderWindow& window) {
    GameObject::render(window);  // Simply call the base class render
}

// Get the global bounds of the image
sf::FloatRect Image::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

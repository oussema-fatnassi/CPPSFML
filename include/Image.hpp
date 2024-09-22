#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "GameObject.hpp"

class Image : public GameObject {
public:
    Image(sf::Vector2f position, sf::Vector2f dimension, const std::string& imagePath);
    ~Image() = default;

    void render(sf::RenderWindow& window) override;  // Use the inherited render function
    sf::FloatRect getGlobalBounds() const;  // Get the global bounds of the image
};

#endif  // IMAGE_HPP

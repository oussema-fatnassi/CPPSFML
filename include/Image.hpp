#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "GameObject.hpp"

class Image : public GameObject {
public:
    Image(sf::Vector2f position, sf::Vector2f dimension, const std::string& imagePath);
    ~Image() = default;

    void render(sf::RenderWindow& window) override;  // Use the inherited render function
};

#endif  // IMAGE_HPP

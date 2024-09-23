#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "GameObject.hpp"

class Image : public GameObject {
public:
    Image(sf::Vector2f position, sf::Vector2f dimension, const std::string& imagePath);         // Constructor
    ~Image() = default;                                                                         // Destructor        

    void render(sf::RenderWindow& window) override;  
    sf::FloatRect getGlobalBounds() const;                                                      // Getter
};

#endif  // IMAGE_HPP

#ifndef BRICK_HPP
#define BRICK_HPP

#include "GameObject.hpp"

class Brick : public GameObject {
public:
    Brick(sf::Vector2f position, sf::Vector2f dimension, const string& imagePath, int health);
    void render(sf::RenderWindow& window) override;
    int getHealth() const;
    sf::FloatRect getGlobalBounds() const;
    sf::Vector2f getNormal(const sf::Vector2f& collisionPoint) const;

    void reduceHealth(int damage);
    
    // Add this method to check if the brick is destroyed
    bool isDestroyed() const;

private:
    int health;
};

#endif // BRICK_HPP
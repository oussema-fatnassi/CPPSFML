#ifndef BRICK_HPP
#define BRICK_HPP

#include "GameObject.hpp"

class Brick : public GameObject {
public:
    Brick(int x, int y, int width, int height, const string& imagePath, int health);
    void render(sf::RenderWindow& window) override;
    int getHealth() const;
    sf::FloatRect getBounds() const;
    sf::Vector2f getNormal(const sf::Vector2f& collisionPoint);

private:
    int health;
};

#endif // BRICK_HPP
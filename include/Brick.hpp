#ifndef BRICK_HPP
#define BRICK_HPP

#include "GameObject.hpp"

class Brick : public GameObject {
public:
    Brick(sf::RenderWindow& window, int x, int y, int width, int height, const string& imagePath, int health);
    void render() override;
    int getHealth() const;

private:
    int health;
};

#endif // BRICK_HPP
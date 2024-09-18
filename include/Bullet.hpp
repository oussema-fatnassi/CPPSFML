#ifndef BULLET_HPP
#define BULLET_HPP

#include "GameObject.hpp"
#include "Brick.hpp"
#include <cmath>

class Bullet : public GameObject {
public:
    Bullet(sf::Vector2f position, sf::Vector2f dimension, const string& imagePath, float rotation, float speed, int damage);
    void update();
    void render(sf::RenderWindow& window) override;

    int getDamage() const;
    float getSpeed() const;
    float getRotation() const;
    void isColliding(std::vector<Brick>& bricks, sf::RenderWindow& window);

private:
    float rotation;
    float speed;
    int damage;
};

#endif // BULLET_HPP
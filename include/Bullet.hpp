#ifndef BULLET_HPP
#define BULLET_HPP

#include "GameObject.hpp"

class Bullet : public GameObject {
public:
    Bullet(sf::RenderWindow& window, int x, int y, int width, int height, const string& imagePath, float rotation, float speed, int damage);
    void update();
    void render() override;

    int getDamage() const;
    float getSpeed() const;
    float getRotation() const;

private:
    float rotation;
    float speed;
    int damage;
};

#endif // BULLET_HPP
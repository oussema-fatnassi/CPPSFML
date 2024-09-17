#ifndef CANNON_HPP
#define CANNON_HPP

#include "GameObject.hpp"

class Cannon : public GameObject {
public:
    Cannon(int x, int y, int width, int height, const string& imagePath);
    void render(sf::RenderWindow& window) override;
    void setRotation(float rotation);
    float getRotation() const;
    void updateRotation(sf::RenderWindow& window);
    void shoot();

private:
    float rotation;
};

#endif // CANNON_HPP
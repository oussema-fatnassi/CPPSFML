#ifndef CANNON_HPP
#define CANNON_HPP

#include "GameObject.hpp"

class Cannon : public GameObject {
public:
    Cannon(sf::RenderWindow& window, int x, int y, int width, int height, const string& imagePath);
    void render() override;
    void setRotation(float rotation);
    float getRotation() const;
    void updateRotation();
    void shoot();

private:
    float rotation;
};

#endif // CANNON_HPP
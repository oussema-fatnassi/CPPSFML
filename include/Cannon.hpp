#ifndef CANNON_HPP
#define CANNON_HPP

#include "GameObject.hpp"

class Cannon : public GameObject {
public:
    Cannon(sf::RenderWindow& window, int x, int y, int width, int height, const string& imagePath, float rotation);
    void render() override;
    void setRotation(float rotation);
    float getRotation() const;
    void updateRotation();

private:
    float rotation;
};

#endif // CANNON_HPP
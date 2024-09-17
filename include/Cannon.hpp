#ifndef CANNON_HPP
#define CANNON_HPP

#include "GameObject.hpp"
#include "InputManager.hpp"
#include "Bullet.hpp"
#include "MathHelper.hpp"
#include <cmath>

class Cannon : public GameObject {
public:
    Cannon(int x, int y, int width, int height, const string& imagePath);
    void render(sf::RenderWindow& window) override;
    void setRotation(float rotation);
    float getRotation() const;
    void updateRotation(sf::RenderWindow& window);
    sf::VertexArray drawTrajectory(sf::RenderWindow& window);

private:
    float rotation;
    float calculateLineEnd(sf::Vector2f& lineEnd, const sf::Vector2f& direction, const sf::Vector2u& windowSize);
    sf::Vector2f determineBorderNormal(const sf::Vector2f& lineEnd, const sf::Vector2u& windowSize);
    sf::Vector2f reflectDirection(const sf::Vector2f& direction, const sf::Vector2f& normal);
};

#endif // CANNON_HPP
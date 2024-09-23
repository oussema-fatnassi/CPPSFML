#ifndef CANNON_HPP
#define CANNON_HPP

#include "TrajectoryManager.hpp"
#include "InputManager.hpp"
#include "GameObject.hpp"
#include "MathHelper.hpp"
#include "SoundManager.hpp"
#include "Bullet.hpp"
#include <cmath>
#include <vector>
using namespace std;

class Cannon : public GameObject {
public:
    Cannon(sf::Vector2f position, sf::Vector2f dimension, const string& imagePath, SoundManager* soundManager);
    void render(sf::RenderWindow& window) override;
    void setRotation(float rotation);
    float getRotation() const;
    void updateRotation(sf::RenderWindow& window);
    void drawTrajectory(sf::RenderWindow& window);
    Bullet shoot();

    sf::Vector2f getPosition() const;
private:
    float rotation;
    float calculateLineEnd(sf::Vector2f& lineEnd, const sf::Vector2f& direction, const sf::Vector2u& windowSize);
    sf::Vector2f determineBorderNormal(const sf::Vector2f& lineEnd, const sf::Vector2u& windowSize);
    sf::Vector2f reflectDirection(const sf::Vector2f& direction, const sf::Vector2f& normal);
    TrajectoryManager trajectoryManager;
    SoundManager* soundManager;

};

#endif // CANNON_HPP
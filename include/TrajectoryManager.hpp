#ifndef TRAJECTORY_MANAGER_HPP
#define TRAJECTORY_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include "MathHelper.hpp"
#include <vector>
#include <limits>
#include <cmath>

class Brick;

class TrajectoryManager  {
public:
    TrajectoryManager();                                 // Constructor
    void updateTrajectory(sf::Vector2f startPoint, sf::Vector2f direction, sf::RenderWindow& window, float maxY);
    virtual void onBorderCollision(sf::Vector2f& trajectoryPoint, sf::Vector2f& direction, const sf::Vector2u& windowSize) ;

private:
    void drawTrajectory(sf::RenderWindow& window, const sf::VertexArray& trajectoryLine);
    float calculateLineEnd(sf::Vector2f& lineEnd, const sf::Vector2f& direction, const sf::Vector2u& windowSize);
    sf::Vector2f determineBorderNormal(const sf::Vector2f& lineEnd, const sf::Vector2u& windowSize);

};

#endif // TRAJECTORY_MANAGER_HPP

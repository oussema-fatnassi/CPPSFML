#ifndef TRAJECTORY_OBSERVER_HPP
#define TRAJECTORY_OBSERVER_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Brick; // Forward declaration

class TrajectoryObserver {
public:
    virtual void onBrickCollision(sf::Vector2f& trajectoryPoint, sf::Vector2f& direction, const Brick& brick) = 0;
    virtual void onBorderCollision(sf::Vector2f& trajectoryPoint, sf::Vector2f& direction, const sf::Vector2u& windowSize) = 0;
};

#endif // TRAJECTORY_OBSERVER_HPP

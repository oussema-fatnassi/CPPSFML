#ifndef TRAJECTORY_MANAGER_HPP
#define TRAJECTORY_MANAGER_HPP

#include "TrajectoryObserver.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include "MathHelper.hpp"

class Brick;

class TrajectoryManager : public TrajectoryObserver {
public:
    TrajectoryManager();

    void updateTrajectory(sf::Vector2f startPoint, sf::Vector2f direction, sf::RenderWindow& window, const std::vector<Brick>& bricks);

    virtual void onBrickCollision(sf::Vector2f& trajectoryPoint, sf::Vector2f& direction, const Brick& brick) override;
    virtual void onBorderCollision(sf::Vector2f& trajectoryPoint, sf::Vector2f& direction, const sf::Vector2u& windowSize) override;

private:
    void drawTrajectory(sf::RenderWindow& window, const sf::VertexArray& trajectoryLine);
    float calculateLineEnd(sf::Vector2f& lineEnd, const sf::Vector2f& direction, const sf::Vector2u& windowSize);
    sf::Vector2f determineBorderNormal(const sf::Vector2f& lineEnd, const sf::Vector2u& windowSize);

};

#endif // TRAJECTORY_MANAGER_HPP

#include "TrajectoryManager.hpp"
#include <cmath>
#include <limits>

TrajectoryManager::TrajectoryManager() {}

void TrajectoryManager::updateTrajectory(sf::Vector2f startPoint, sf::Vector2f direction, sf::RenderWindow& window) {
    sf::Vector2f currentPoint = startPoint;
    sf::VertexArray trajectoryLine(sf::LinesStrip);
    trajectoryLine.append(sf::Vertex(currentPoint, sf::Color::Red));

    sf::Vector2u windowSize = window.getSize();
    int maxReflections = 15;

    while (maxReflections > 0) {
        sf::Vector2f nextPoint = currentPoint;
        float t_min = calculateLineEnd(nextPoint, direction, windowSize);

        if (nextPoint.y >= windowSize.y) {
            float t_bottom = (windowSize.y - currentPoint.y) / direction.y;
            if (t_bottom > 0) {
                nextPoint = currentPoint + t_bottom * direction;
                trajectoryLine.append(sf::Vertex(nextPoint, sf::Color::Red));
                break;
            }
        }

        onBorderCollision(nextPoint, direction, windowSize);

        currentPoint = nextPoint;
        trajectoryLine.append(sf::Vertex(currentPoint, sf::Color::Red));
        maxReflections--;
    }

    drawTrajectory(window, trajectoryLine);
}


void TrajectoryManager::onBorderCollision(sf::Vector2f& trajectoryPoint, sf::Vector2f& direction, const sf::Vector2u& windowSize) {
    sf::Vector2f normal = determineBorderNormal(trajectoryPoint, windowSize);
    if (normal == sf::Vector2f(0, -1)) {
        float t_bottom = (windowSize.y - trajectoryPoint.y) / direction.y;
        if (t_bottom > 0) {
            trajectoryPoint = trajectoryPoint + t_bottom * direction;
        }
    } else {
        direction = MathHelper::reflectDirection(direction, normal);
    }
}

void TrajectoryManager::drawTrajectory(sf::RenderWindow& window, const sf::VertexArray& trajectoryLine) {
    window.draw(trajectoryLine);
}

float TrajectoryManager::calculateLineEnd(sf::Vector2f& lineEnd, const sf::Vector2f& direction, const sf::Vector2u& windowSize) {
    float t_max_x, t_max_y;

    if (direction.x != 0) {
        t_max_x = (direction.x > 0) ? (windowSize.x - lineEnd.x) / direction.x : (-lineEnd.x) / direction.x;
    } else {
        t_max_x = std::numeric_limits<float>::max(); // No movement in x direction
    }

    if (direction.y != 0) {
        t_max_y = (direction.y > 0) ? (windowSize.y - lineEnd.y) / direction.y : (-lineEnd.y) / direction.y;
    } else {
        t_max_y = std::numeric_limits<float>::max(); // No movement in y direction
    }

    float t_min = std::min(t_max_x, t_max_y);
    lineEnd = lineEnd + direction * t_min;

    return t_min;
}

sf::Vector2f TrajectoryManager::determineBorderNormal(const sf::Vector2f& lineEnd, const sf::Vector2u& windowSize) {
    if (lineEnd.x <= 0) {
        return sf::Vector2f(1, 0); // Left border
    } else if (lineEnd.x >= windowSize.x) {
        return sf::Vector2f(-1, 0); // Right border
    } else if (lineEnd.y <= 0) {
        return sf::Vector2f(0, 1); // Top border
    } else if (lineEnd.y >= windowSize.y) {
        return sf::Vector2f(0, -1); // Bottom border
    }
    return sf::Vector2f(0, 0); // No border hit
}

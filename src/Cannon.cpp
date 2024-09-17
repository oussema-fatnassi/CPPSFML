#include "Cannon.hpp"

Cannon::Cannon(int x, int y, int width, int height, const string& imagePath)
    : GameObject(x, y, width, height, imagePath) {
    loadTexture(imagePath);
    sprite.setOrigin(width / 2.f, height /1.23f); 
    sprite.setRotation(rotation);
}

void Cannon::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Cannon::updateRotation(sf::RenderWindow& window) {
    sf::Vector2i mousePos = InputManager::getInstance().getMousePosition(window);
    sf::Vector2f cannonPos = sprite.getPosition();

    // Check if the mouse is above the cannon
    if (mousePos.y < cannonPos.y) {
        // Mouse is above the cannon, calculate the rotation angle
        float angle = MathHelper::getAngle(cannonPos.x, cannonPos.y, mousePos.x, mousePos.y);

        // Adjust the angle for the initial orientation of the cannon
        angle += 180.0f;

        // Set the new rotation
        setRotation(angle);
    }
    // If the mouse is below the cannon, do nothing (rotation remains unchanged)
}


void Cannon::setRotation(float rotation) {
    this->rotation = rotation;
    sprite.setRotation(rotation);
}

float Cannon::getRotation() const {
    return rotation;
}

void Cannon::drawTrajectory(sf::RenderWindow& window) {
sf::Vector2f cannonPos = sprite.getPosition();
    float angle = getRotation();

    // Convert the angle from degrees to radians
    float radians = (angle - 90.f) * 3.14159265f / 180.0f;

    // Calculate the initial direction vector based on the cannon's rotation
    sf::Vector2f direction(std::cos(radians), std::sin(radians));
    sf::Vector2u windowSize = window.getSize();

    // Start the trajectory from the cannon position
    sf::Vector2f startPoint = cannonPos;
    sf::Vector2f currentDirection = direction;
    sf::Vector2f currentPoint = startPoint;

    sf::VertexArray trajectoryLine(sf::LinesStrip);
    trajectoryLine.append(sf::Vertex(startPoint, sf::Color::Red));

    while (currentPoint.y < windowSize.y) {
        sf::Vector2f nextPoint = currentPoint;
        float t_min = calculateLineEnd(nextPoint, currentDirection, windowSize);

        // Break if no intersection found
        if (t_min <= 0) break;

        // Calculate the reflection
        sf::Vector2f normal = determineBorderNormal(nextPoint, windowSize);
        currentDirection = reflectDirection(currentDirection, normal);

        // Update the current point
        currentPoint = nextPoint;

        // Append the new point to the trajectory
        trajectoryLine.append(sf::Vertex(currentPoint, sf::Color::Red));
    }

    // Draw the trajectory line
    window.draw(trajectoryLine);
}

float Cannon::calculateLineEnd(sf::Vector2f& lineEnd, const sf::Vector2f& direction, const sf::Vector2u& windowSize) {
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

    // Use the smaller t_max value to find the intersection point
    float t_min = std::min(t_max_x, t_max_y);
    lineEnd = lineEnd + direction * t_min;

    return t_min;
}

sf::Vector2f Cannon::determineBorderNormal(const sf::Vector2f& lineEnd, const sf::Vector2u& windowSize) {
    if (lineEnd.x <= 0) {
        return sf::Vector2f(1, 0); // Left border
    } else if (lineEnd.x >= windowSize.x) {
        return sf::Vector2f(-1, 0); // Right border
    } else if (lineEnd.y <= 0) {
        return sf::Vector2f(0, 1); // Top border
    } else if (lineEnd.y >= windowSize.y) {
        return sf::Vector2f(0, -1); // Bottom border
    }
    // Default value if no border hit, should not occur
    return sf::Vector2f(0, 0);
}

sf::Vector2f Cannon::reflectDirection(const sf::Vector2f& direction, const sf::Vector2f& normal) {
    // Reflect the direction vector around the normal
    float dotProduct = MathHelper::dotProduct(direction, normal);
    return direction - 2 * dotProduct * normal;
}

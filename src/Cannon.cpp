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

void Cannon::drawTrajectory(sf::RenderWindow& window, const std::vector<Brick>& bricks) {
    sf::Vector2f cannonPos = sprite.getPosition();
    float angle = getRotation();
    float radians = (angle - 90.f) * 3.14159265f / 180.0f;
    sf::Vector2f direction(std::cos(radians), std::sin(radians));
    trajectoryManager.updateTrajectory(cannonPos, direction, window, bricks);
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
        return sf::Vector2f(0, -1); // Bottom border, used to stop the trajectory
    }
    return sf::Vector2f(0, 0); // No border hit
}


sf::Vector2f Cannon::reflectDirection(const sf::Vector2f& direction, const sf::Vector2f& normal) {
    // Reflect the direction vector around the normal
    float dotProduct = MathHelper::dotProduct(direction, normal);
    return direction - 2 * dotProduct * normal;
}

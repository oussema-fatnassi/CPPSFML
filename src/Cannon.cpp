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

sf::VertexArray Cannon::drawTrajectory(sf::RenderWindow& window, std::vector<Brick>& bricks) {
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

    int maxReflections = 5;

    while (maxReflections > 0) {
        sf::Vector2f nextPoint = currentPoint;
        float t_min = calculateLineEnd(nextPoint, currentDirection, windowSize);

        // Check if the trajectory intersects the bottom border
        if (nextPoint.y >= windowSize.y) {
            // Calculate the intersection point with the bottom border
            float t_bottom = (windowSize.y - currentPoint.y) / currentDirection.y;
            if (t_bottom > 0) {
                nextPoint = currentPoint + t_bottom * currentDirection;
                // Draw up to the bottom border and stop
                trajectoryLine.append(sf::Vertex(nextPoint, sf::Color::Red));
                break; // Exit if it hits the bottom border
            }
        }

        // Check for collisions with bricks
        bool brickCollision = false;
        Brick* collidedBrick = nullptr;
        for (auto& brick : bricks) {
            if (MathHelper::lineIntersectsRectangle(currentPoint, nextPoint, brick.getBounds())) {
                // Collision detected with a brick
                brickCollision = true;
                collidedBrick = &brick;

                // Calculate the intersection point with the external boundaries of the brick
                nextPoint = MathHelper::calculateIntersectionPoint(currentPoint, nextPoint, brick.getBounds());

                // Calculate the reflection based on the correct side of the brick (external boundaries)
                sf::Vector2f normal = collidedBrick->getNormal(nextPoint);
                currentDirection = MathHelper::reflectDirection(currentDirection, normal);

                break;
            }
        }

        // If no brick collision, check for collisions with window border
        if (!brickCollision) {
            sf::Vector2f normal = determineBorderNormal(nextPoint, windowSize);

            // If it hits the bottom border, draw up to it and stop
            if (normal == sf::Vector2f(0, -1)) {
                float t_bottom = (windowSize.y - currentPoint.y) / currentDirection.y;
                if (t_bottom > 0) {
                    nextPoint = currentPoint + t_bottom * currentDirection;
                    trajectoryLine.append(sf::Vertex(nextPoint, sf::Color::Red));
                    break; // Exit if it hits the bottom border
                }
            } else {
                // Calculate the reflection from the window border
                currentDirection = MathHelper::reflectDirection(currentDirection, normal);
            }
        }

        // Update the current point
        currentPoint = nextPoint;

        // Append the new point to the trajectory
        trajectoryLine.append(sf::Vertex(currentPoint, sf::Color::Red));

        maxReflections--;
    }

    // Draw the trajectory line
    window.draw(trajectoryLine);
    return trajectoryLine;
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

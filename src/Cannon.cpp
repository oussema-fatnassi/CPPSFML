#include "Cannon.hpp"
#include "InputManager.hpp"
#include <cmath>
#include "Bullet.hpp"

float getAngle(float x1, float y1, float x2, float y2) {
    sf::Vector2f up(0, 1);
    sf::Vector2f p0(x1, y1);
    sf::Vector2f p1(x2, y2);
    sf::Vector2f q = p1 - p0;

    float q_length = std::sqrt(q.x * q.x + q.y * q.y);

    q.x /= q_length;
    q.y /= q_length;

    float scalar_product = q.y;

    float angle = std::acos(scalar_product) * 180.0f / 3.1415f;

    if (x2 - x1 < 0.0f)
        return angle;
    else
        return -angle;
}

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
        float angle = getAngle(cannonPos.x, cannonPos.y, mousePos.x, mousePos.y);

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

// Helper function to calculate intersection and normal
bool intersects(const sf::Vector2f& start1, const sf::Vector2f& end1,
                const sf::Vector2f& start2, const sf::Vector2f& end2,
                sf::Vector2f& normal) {
    sf::Vector2f dir1 = end1 - start1;
    sf::Vector2f dir2 = end2 - start2;
    sf::Vector2f diff = start1 - start2;

    float det = dir1.x * dir2.y - dir1.y * dir2.x;
    if (det == 0) return false; // Parallel lines

    float t = (diff.x * dir2.y - diff.y * dir2.x) / det;
    float u = (diff.x * dir1.y - diff.y * dir1.x) / det;

    if (t >= 0 && t <= 1 && u >= 0) {
        normal = dir2;
        normal = sf::Vector2f(-normal.y, normal.x); // Perpendicular vector
        return true;
    }
    return false;
}

// Helper function to reflect the direction vector off the normal
sf::Vector2f reflect(const sf::Vector2f& direction, const sf::Vector2f& normal) {
    float dotProduct = direction.x * normal.x + direction.y * normal.y;
    return direction - 2 * dotProduct * normal;
}

void Cannon::drawTrajectory(sf::RenderWindow& window) {
    sf::Vector2f cannonPos = sprite.getPosition();
    float angle = getRotation();

    // Convert the angle from degrees to radians
    float radians = (angle - 90.f) * 3.14159265f / 180.0f;

    // Calculate the direction vector based on the cannon's rotation
    sf::Vector2f direction(std::cos(radians), std::sin(radians));

    // Define window boundaries
    sf::IntRect viewport = window.getViewport(window.getView());
    sf::Vector2f topLeft(0, 0);
    sf::Vector2f bottomRight(600, 900);  // Width x Height of the window

    // Initialize the start and end points of the trajectory
    sf::Vector2f start = cannonPos;
    sf::Vector2f end = start + direction * 2000.f;

    // Line parameters
    sf::Vector2f normal;
    bool hit = false;

    // Check for intersection with window borders
    while (end.y >= 0) {
        // Check intersections with window borders
        sf::Vector2f borderStart, borderEnd;

        // Top border
        borderStart = topLeft;
        borderEnd = sf::Vector2f(bottomRight.x, topLeft.y);
        if (intersects(start, end, borderStart, borderEnd, normal)) {
            hit = true;
        }

        // Left border
        if (!hit) {
            borderStart = topLeft;
            borderEnd = sf::Vector2f(topLeft.x, bottomRight.y);
            if (intersects(start, end, borderStart, borderEnd, normal)) {
                hit = true;
            }
        }

        // Right border
        if (!hit) {
            borderStart = sf::Vector2f(bottomRight.x, topLeft.y);
            borderEnd = bottomRight;
            if (intersects(start, end, borderStart, borderEnd, normal)) {
                hit = true;
            }
        }

        if (hit) {
            // Reflect the direction vector
            direction = reflect(direction, normal);
            // Update the end point
            end = start + direction * 2000.f;
            // Reset the hit flag
            hit = false;
        } else {
            // No intersection, break the loop
            break;
        }
    }

    // Draw the trajectory line
    sf::VertexArray trajectoryLine(sf::Lines, 2);
    trajectoryLine[0].position = start;
    trajectoryLine[0].color = sf::Color::Red;
    trajectoryLine[1].position = end;
    trajectoryLine[1].color = sf::Color::Red;
    window.draw(trajectoryLine);
}


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

void Cannon::drawTrajectory(sf::RenderWindow& window) {
    sf::Vector2f cannonPos = sprite.getPosition();
    float angle = getRotation();

    // Convert the angle from degrees to radians
    float radians = (angle-90.f) * 3.14159265f / 180.0f;

    // Calculate the direction vector based on the cannon's rotation
    sf::Vector2f direction(std::cos(radians), std::sin(radians));

    // Scale the direction to a desired length
    float lineLength = 2000.f;
    sf::Vector2f lineEnd = cannonPos + direction * lineLength;

    // Draw the trajectory line
    sf::VertexArray trajectoryLine(sf::Lines, 2);
    trajectoryLine[0].position = cannonPos;
    trajectoryLine[0].color = sf::Color::Red;
    trajectoryLine[1].position = lineEnd;
    trajectoryLine[1].color = sf::Color::Red;
    window.draw(trajectoryLine);
}


// void Cannon::shoot() {
//     sf::Vector2f cannonPos = sprite.getPosition();
//     float angle = getRotation();

//     float x = cannonPos.x + 50 * cos(angle * 3.14159265 / 180);
//     float y = cannonPos.y + 50 * sin(angle * 3.14159265 / 180);

//     Bullet* bullet = new Bullet(window, x, y, 10, 10, "assets/bullet.png", angle, 5.0f, 1);
//     AssetManager::getInstance().addBullet(bullet);
// }
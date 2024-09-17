#include "Cannon.hpp"
#include "InputManager.hpp"
#include <cmath>

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

Cannon::Cannon(sf::RenderWindow& window, int x, int y, int width, int height, const string& imagePath, float rotation)
    : GameObject(window, x, y, width, height, imagePath), rotation(rotation) {
    loadTexture(imagePath);
    sprite.setOrigin(width / 2.f, height /1.23f); // set the origin to the middle point of the top border
    sprite.setRotation(rotation);
}

void Cannon::render() {
    window.draw(sprite);
}

void Cannon::updateRotation() {
    sf::Vector2i mousePos = InputManager::getInstance().getMousePosition(window);
    sf::Vector2f cannonPos = sprite.getPosition();

    float angle = getAngle(cannonPos.x, cannonPos.y, mousePos.x, mousePos.y);

    angle += 180.0f;

    setRotation(angle);
}

void Cannon::setRotation(float rotation) {
    this->rotation = rotation;
    sprite.setRotation(rotation);
}

float Cannon::getRotation() const {
    return rotation;
}

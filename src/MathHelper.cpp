#include "MathHelper.hpp"

float MathHelper::getAngle(float x1, float y1, float x2, float y2) {
    sf::Vector2f up(0, 1);
    sf::Vector2f p0(x1, y1);
    sf::Vector2f p1(x2, y2);
    sf::Vector2f q = p1 - p0;

    float q_length = magnitude(q);

    q.x /= q_length;
    q.y /= q_length;

    float scalar_product = q.y;

    float angle = std::acos(scalar_product) * 180.0f / 3.1415f;

    if (x2 - x1 < 0.0f)
        return angle;
    else
        return -angle;
}

float MathHelper::dotProduct(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

float MathHelper::magnitude(const sf::Vector2f& v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

float MathHelper::calculateCollisionAngle(const sf::Vector2f& direction, const sf::Vector2f& normal) {
    // Normalize the direction vector
    float dirLength = magnitude(direction);
    sf::Vector2f normalizedDirection = direction / dirLength;

    // Calculate the dot product
    float dot = dotProduct(normalizedDirection, normal);

    // Calculate the angle between the direction and the normal (in degrees)
    return std::acos(dot) * 180.0f / 3.14159265f;
}

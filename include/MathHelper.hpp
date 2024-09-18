#ifndef MATH_HELPER_HPP
#define MATH_HELPER_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

class MathHelper {
public:
    // Calculates the angle between two points
    static float getAngle(float x1, float y1, float x2, float y2);

    // Calculates the dot product between two vectors
    static float dotProduct(const sf::Vector2f& v1, const sf::Vector2f& v2);

    // Calculates the magnitude of a vector
    static float magnitude(const sf::Vector2f& v);

    // Calculates the collision angle between a direction vector and a surface normal
    static float calculateCollisionAngle(const sf::Vector2f& direction, const sf::Vector2f& normal);

    // Checks if a line intersects a rectangle
    bool lineIntersectsRectangle(const sf::Vector2f& lineStart, const sf::Vector2f& lineEnd, const sf::FloatRect& rect);

    // Reflect the direction vector around the normal
    static sf::Vector2f reflectDirection(const sf::Vector2f& direction, const sf::Vector2f& normal) {
        float dotProduct = MathHelper::dotProduct(direction, normal);
        return direction - 2 * dotProduct * normal;
    }
};

#endif // MATH_HELPER_HPP

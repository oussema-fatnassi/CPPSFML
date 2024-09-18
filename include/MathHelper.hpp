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
    static bool lineIntersectsRectangle(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::FloatRect& rect);

    static bool lineIntersectsLine(const sf::Vector2f& a1, const sf::Vector2f& a2, 
                                    const sf::Vector2f& b1, const sf::Vector2f& b2);

    static sf::Vector2f reflectDirection(const sf::Vector2f& incident, const sf::Vector2f& normal);

    static sf::Vector2f calculateIntersectionPoint(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::FloatRect& rect);

    static sf::Vector2f getLineIntersection(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& q1, const sf::Vector2f& q2);
};

#endif // MATH_HELPER_HPP

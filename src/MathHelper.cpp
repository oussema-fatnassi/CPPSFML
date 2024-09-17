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

bool MathHelper::lineIntersectsRectangle(const sf::Vector2f& lineStart, const sf::Vector2f& lineEnd, const sf::FloatRect& rect) {
    // Calculate the line vector
    sf::Vector2f line = lineEnd - lineStart;

    // Calculate the rectangle edges
    sf::Vector2f rectEdges[4] = {
        sf::Vector2f(1, 0), // Right edge
        sf::Vector2f(0, 1), // Bottom edge
        sf::Vector2f(-1, 0), // Left edge
        sf::Vector2f(0, -1) // Top edge
    };

    // Calculate the line's normal vectors
    sf::Vector2f lineNormals[2] = {
        sf::Vector2f(-line.y, line.x), // Normal to the line (counter-clockwise)
        sf::Vector2f(line.y, -line.x) // Normal to the line (clockwise)
    };

    // Check for separation on all edges and normals
    for (int i = 0; i < 4; i++) {
        // Calculate the rectangle's edge vector
        sf::Vector2f rectEdge = rectEdges[i];

        // Calculate the rectangle's normal vector
        sf::Vector2f rectNormal = sf::Vector2f(-rectEdge.y, rectEdge.x);

        // Calculate the minimum and maximum projections of the line and rectangle on the normal
        float lineMin = dotProduct(lineStart, rectNormal);
        float lineMax = dotProduct(lineEnd, rectNormal);
        float rectMin = dotProduct(sf::Vector2f(rect.left, rect.top), rectNormal);
        float rectMax = dotProduct(sf::Vector2f(rect.left + rect.width, rect.top + rect.height), rectNormal);

        // Swap the minimum and maximum values if necessary
        if (lineMin > lineMax) std::swap(lineMin, lineMax);
        if (rectMin > rectMax) std::swap(rectMin, rectMax);

        // Check for separation
        if (lineMax < rectMin || lineMin > rectMax) {
            return false;
        }
    }

    // No separation found, the line intersects the rectangle
    return true;
}
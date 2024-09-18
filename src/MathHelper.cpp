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

bool MathHelper::lineIntersectsRectangle(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::FloatRect& rect) {
    // Check if the line from p1 to p2 intersects any side of the rectangle
    sf::Vector2f topLeft(rect.left, rect.top);
    sf::Vector2f topRight(rect.left + rect.width, rect.top);
    sf::Vector2f bottomLeft(rect.left, rect.top + rect.height);
    sf::Vector2f bottomRight(rect.left + rect.width, rect.top + rect.height);

    // Check if the line intersects any of the four sides of the rectangle
    return MathHelper::lineIntersectsLine(p1, p2, topLeft, topRight) || 
           MathHelper::lineIntersectsLine(p1, p2, topRight, bottomRight) ||
           MathHelper::lineIntersectsLine(p1, p2, bottomRight, bottomLeft) ||
           MathHelper::lineIntersectsLine(p1, p2, bottomLeft, topLeft);
}


bool MathHelper::lineIntersectsLine(const sf::Vector2f& a1, const sf::Vector2f& a2, 
                                    const sf::Vector2f& b1, const sf::Vector2f& b2) {
    float denominator = (a2.x - a1.x) * (b2.y - b1.y) - (a2.y - a1.y) * (b2.x - b1.x);
    
    // If the denominator is 0, the lines are parallel
    if (denominator == 0.0f) return false;

    float ua = ((b2.x - b1.x) * (a1.y - b1.y) - (b2.y - b1.y) * (a1.x - b1.x)) / denominator;
    float ub = ((a2.x - a1.x) * (a1.y - b1.y) - (a2.y - a1.y) * (a1.x - b1.x)) / denominator;

    // If both ua and ub are between 0 and 1, the lines intersect
    return (ua >= 0.0f && ua <= 1.0f && ub >= 0.0f && ub <= 1.0f);
}

sf::Vector2f MathHelper::reflectDirection(const sf::Vector2f& incident, const sf::Vector2f& normal) {
    return incident - 2.0f * MathHelper::dotProduct(incident, normal) * normal;
}


sf::Vector2f MathHelper::calculateIntersectionPoint(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::FloatRect& rect) {
    // Find the intersection point of the line from p1 to p2 with the rectangle
    // This function assumes that an intersection exists

    sf::Vector2f topLeft(rect.left, rect.top);
    sf::Vector2f topRight(rect.left + rect.width, rect.top);
    sf::Vector2f bottomLeft(rect.left, rect.top + rect.height);
    sf::Vector2f bottomRight(rect.left + rect.width, rect.top + rect.height);

    // Check which side of the rectangle the line intersects
    if (MathHelper::lineIntersectsLine(p1, p2, topLeft, topRight)) {
        return MathHelper::getLineIntersection(p1, p2, topLeft, topRight);
    } else if (MathHelper::lineIntersectsLine(p1, p2, topRight, bottomRight)) {
        return MathHelper::getLineIntersection(p1, p2, topRight, bottomRight);
    } else if (MathHelper::lineIntersectsLine(p1, p2, bottomRight, bottomLeft)) {
        return MathHelper::getLineIntersection(p1, p2, bottomRight, bottomLeft);
    } else {
        return MathHelper::getLineIntersection(p1, p2, bottomLeft, topLeft);
    }
}

sf::Vector2f MathHelper::getLineIntersection(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& q1, const sf::Vector2f& q2) {
    // Calculate the intersection point of the lines from p1 to p2 and from q1 to q2
    // This function assumes that an intersection exists

    float denominator = (p2.x - p1.x) * (q2.y - q1.y) - (p2.y - p1.y) * (q2.x - q1.x);
    float t = ((p1.y - q1.y) * (q2.x - q1.x) - (p1.x - q1.x) * (q2.y - q1.y)) / denominator;

    return p1 + t * (p2 - p1);
}

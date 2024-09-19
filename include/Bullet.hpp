#ifndef BULLET_HPP
#define BULLET_HPP

#include "GameObject.hpp"
#include <string>
#include "MathHelper.hpp"
using namespace std;

class Bullet : public GameObject {
public:
    Bullet(sf::Vector2f position, sf::Vector2f dimension, const string& imagePath, float rotation, float speed, int damage);
    ~Bullet(); // Destructor

    void update(const sf::Vector2f& cannonPosition); // Pass the cannon's position to update
    void render(sf::RenderWindow& window) override;

    bool isActive() const;  // Check if the bullet is still active
    void deactivate();      // Deactivate the bullet

private:
    float rotation;
    float speed;
    int damage;
    bool active;  // Flag to track if the bullet is active
    sf::Vector2f velocity;  // Velocity of the bullet
};

#endif // BULLET_HPP

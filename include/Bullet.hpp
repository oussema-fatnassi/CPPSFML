#ifndef BULLET_HPP
#define BULLET_HPP

#include "GameObject.hpp"
#include "MathHelper.hpp"
#include "Brick.hpp"
#include "Image.hpp"
#include <string>
#include <cmath>
using namespace std;

class Bullet : public GameObject {
public:
    Bullet(sf::Vector2f position, sf::Vector2f dimension, const string& imagePath, float rotation, float speed, int damage);
    ~Bullet(); // Destructor

    void update(const sf::Vector2f& cannonPosition, std::vector<Brick>& bricks, std::vector<Image>& walls);
    void render(sf::RenderWindow& window) override;

    bool isActive() const;  // Check if the bullet is still active
    void deactivate();      // Deactivate the bullet

private:
    float rotation;
    float speed;
    int damage;
    bool active;  // Flag to track if the bullet is active
    sf::Vector2f velocity;  // Velocity of the bullet
    void handleBrickCollision(std::vector<Brick>& bricks);
};

#endif // BULLET_HPP

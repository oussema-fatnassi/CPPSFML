#include "Bullet.hpp"
#include <cmath>
Bullet::Bullet(int x, int y, int width, int height, const string& imagePath, float rotation, float speed, int damage) 
    : GameObject(x, y, width, height, imagePath), rotation(rotation), speed(speed), damage(damage) {
    loadTexture(imagePath);
    sprite.setRotation(rotation);
}

void Bullet::update() {
    // Convert the rotation angle from degrees to radians
    float radians = (rotation - 90.f) * 3.14159265f / 180.0f; // Adjusted to align with cannon's rotation
    
    // Calculate the movement direction based on the rotation angle
    sf::Vector2f direction(std::cos(radians), std::sin(radians));

    // Update the bullet's position by moving it in the direction
    sprite.move(direction * speed);
}

void Bullet::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

int Bullet::getDamage() const {
    return damage;
}

float Bullet::getSpeed() const {
    return speed;
}

float Bullet::getRotation() const {
    return rotation;
}
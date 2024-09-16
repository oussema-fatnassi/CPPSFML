#include "Bullet.hpp"

Bullet::Bullet(sf::RenderWindow& window, int x, int y, int width, int height, const string& imagePath, float rotation, float speed, int damage) 
    : GameObject(window, x, y, width, height, imagePath), rotation(rotation), speed(speed), damage(damage) {
    loadTexture(imagePath);
    sprite.setRotation(rotation);
}

void Bullet::update() {
    sprite.move(speed * cos(rotation * 3.14159265 / 180), speed * sin(rotation * 3.14159265 / 180));
}

void Bullet::render() {
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
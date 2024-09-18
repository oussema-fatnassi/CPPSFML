#include "Bullet.hpp"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f dimension, const string& imagePath, float rotation, float speed, int damage) 
    : GameObject(position, dimension, imagePath), rotation(rotation), speed(speed), damage(damage) {
    loadTexture(imagePath);
    sprite.setRotation(rotation);
}

void Bullet::update() {
    sprite.move(speed * cos(rotation * 3.14159265 / 180), speed * sin(rotation * 3.14159265 / 180));
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
/*
void Bullet::isColliding(std::vector<Brick>& bricks, sf::RenderWindow& window) {
    for (auto it = bricks.begin(); it != bricks.end(); ++it) {
        if (this->sprite.getGlobalBounds().intersects(it->getSprite().getGlobalBounds())) {
        sf::FloatRect brickBounds = this->sprite.getGlobalBounds();
            sf::FloatRect brickBounds = it->getSprite().getGlobalBounds();

            // Check from which side the ball is colliding with the brick
            float overlapLeft = brickBounds.left + brickBounds.width - brickBounds.left;
            float overlapRight = brickBounds.left + brickBounds.width - brickBounds.left;
            float overlapTop = brickBounds.top + brickBounds.height - brickBounds.top;
            float overlapBottom = brickBounds.top + brickBounds.height - brickBounds.top;

            // Find the smallest overlap to determine the collision direction
            bool fromLeft = overlapLeft < overlapRight && overlapLeft < overlapTop && overlapLeft < overlapBottom;
            bool fromRight = overlapRight < overlapLeft && overlapRight < overlapTop && overlapRight < overlapBottom;
            bool fromTop = overlapTop < overlapLeft && overlapTop < overlapRight && overlapTop < overlapBottom;
            bool fromBottom = overlapBottom < overlapLeft && overlapBottom < overlapRight && overlapBottom < overlapTop;

            // Adjust the ball's speed based on the side it collided with
            if (fromLeft || fromRight) {
                this->speed.x = -this->speed.x;  // Horizontal collision
            } else if (fromTop || fromBottom) {
                this->speed.y = -this->speed.y;  // Vertical collision
            }

            // Erase the brick
            it = bricks.erase(it);
        } else {
            ++it;
        }
    }

    // Check window bounds for collisions
    if (this->position.x < 0 || this->position.x + this->sprite.getTextureRect().width > window.getSize().x) {
        this->speed.x = -this->speed.x;  // Bounce off left/right window edges
    }
    if (this->position.y < 0) {
        this->speed.y = -this->speed.y;  // Bounce off top window edge
    }
    if (this->position.y + this->sprite.getTextureRect().height > window.getSize().y) {
        this->speed.y = -this->speed.y;  // Bounce off bottom window edge
    }
}*/
  
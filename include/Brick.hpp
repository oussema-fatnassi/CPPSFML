#ifndef BRICK_HPP
#define BRICK_HPP

#include "SoundManager.hpp"
#include "GameObject.hpp"

class Brick : public GameObject {
public:
    Brick(sf::Vector2f position, sf::Vector2f dimension, const string& imagePath, int health, SoundManager* soundManager);      // Constructor
    void render(sf::RenderWindow& window) override;                                                                             // Render the brick         
    void reduceHealth(int damage);
    bool isDestroyed() const;
    sf::FloatRect getGlobalBounds() const;                                                                                      // Getters
    sf::Vector2f getNormal(const sf::Vector2f& collisionPoint) const;
    int getHealth() const;

private:
    int health;                                                                                                                // Member variables                          
    int maxHealth;
    string texturePath;
    SoundManager* soundManager;
    bool isCracked = false;
    string getCrackedTexturePath() const;                                                                                       // Getters      
};

#endif // BRICK_HPP
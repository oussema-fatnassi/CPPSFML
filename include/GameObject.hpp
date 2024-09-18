#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "AssetManager.hpp"
using namespace std;

class GameObject {  
public:
    virtual ~GameObject() = default;                                                              // Destructor    
    virtual void render(sf::RenderWindow& window) = 0;  // Pass window as a parameter in render
    void loadTexture(const string& imagePath);                             

    sf::Vector2f getPosition() const;                                       // Getters
    sf::Vector2f getDimension() const;

    void setTexture(const string& imagePath);                              // Setters     

protected:
    GameObject(sf::Vector2f position, sf::Vector2f dimension, const string& imagePath);  // Constructor

    sf::Vector2f position;                                                  // Member variables
    sf::Vector2f dimension;
    sf::Texture* texture;
    sf::Sprite sprite;
};

#endif  // GAMEOBJECT_HPP

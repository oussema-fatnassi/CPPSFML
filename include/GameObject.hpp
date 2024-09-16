#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "AssetManager.hpp"
using namespace std;

class GameObject {  // GameObject class used for creating game objects (tiles, images)        
public:
    virtual ~GameObject() = default;                                                              // Destructor    
    virtual void render() = 0;
    void loadTexture(const string& imagePath);                             // Public methods

    int getX() const;                                                           // Getters
    int getY() const;
    int getWidth() const;
    int getHeight() const;

    void setTexture(const string& imagePath);                              // Setters     

protected:
    GameObject(sf::RenderWindow& window, int x, int y, int width, int height, const string& imagePath);  // Constructor
    int x;                                                                      // Member variables
    int y;
    int width;
    int height;
    sf::Texture* texture;
    sf::Sprite sprite;
    sf::RenderWindow& window; 
};

#endif  // GAMEOBJECT_HPP
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

    int getX() const;                                                           // Getters
    int getY() const;
    int getWidth() const;
    int getHeight() const;

    void setTexture(const string& imagePath);                              // Setters     

protected:
    GameObject(int x, int y, int width, int height, const string& imagePath);  // Constructor

    int x;                                                                      // Member variables
    int y;
    int width;
    int height;
    sf::Texture* texture;
    sf::Sprite sprite;
};

#endif  // GAMEOBJECT_HPP

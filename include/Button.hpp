#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "GameObject.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>
#include <iostream>
using namespace std;

class Button : public GameObject {
public:
    enum class ButtonState { NORMAL, HOVER, PRESSED };                                                      // Enum for button states
    Button(sf::Vector2f position, sf::Vector2f dimension, const string& normalImage, const string& hoverImage, const string& pressedImage, const function<void()>& onClick);        // Constructor
    ~Button();                                                                                              // Destructor         

    void update(const sf::Vector2f& mousePosition, bool isPressed);     
    void render(sf::RenderWindow& window) override;
    bool isPressed() const;     
    void setText(const string& text, const sf::Font& font, unsigned int characterSize);                     // Setter

private:
    sf::Text buttonText;                                                                                    // Member variables
    sf::Texture normalTexture; 
    sf::Texture hoverTexture; 
    sf::Texture pressedTexture; 
    ButtonState currentState;
    function<void()> onClick;
};

#endif // BUTTON_HPP
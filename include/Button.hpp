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
    enum class ButtonState { NORMAL, HOVER, PRESSED };
    Button(sf::Vector2f position, sf::Vector2f dimension, const string& normalImage, const string& hoverImage, const string& pressedImage, const function<void()>& onClick);
    ~Button(); 

    void setText(const string& text, const sf::Font& font, unsigned int characterSize); // Set the text of the button
    void update(const sf::Vector2f& mousePosition, bool isPressed); // Update the button state
    void render(sf::RenderWindow& window) override;
    bool isPressed() const; // Check if the button is pressed

private:
    sf::Text buttonText; // Text displayed on the button
    sf::Texture normalTexture; // Texture for the normal state
    sf::Texture hoverTexture; // Texture for the hover state
    sf::Texture pressedTexture; // Texture for the pressed state
    ButtonState currentState; // Current state of the button
    function<void()> onClick;
};

#endif // BUTTON_HPP
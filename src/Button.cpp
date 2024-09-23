#include "Button.hpp"
#include "AssetManager.hpp"

/*
    Button class implementation for the game's buttons
*/

Button::Button(sf::Vector2f position, sf::Vector2f dimension, const string& normalImage, const string& hoverImage, const string& pressedImage, const function<void()>& onClick)
    : GameObject(position, dimension, normalImage), currentState(ButtonState::NORMAL), onClick(onClick) {
    
    // Load textures using AssetManager
    normalTexture = *AssetManager::getInstance().getTexture(normalImage);
    hoverTexture = *AssetManager::getInstance().getTexture(hoverImage);
    pressedTexture = *AssetManager::getInstance().getTexture(pressedImage);

    // Set the initial texture to the normal state texture
    sprite.setTexture(normalTexture);
}

// Destructor (nothing specific needed, but it's here if needed)
Button::~Button() {}

// Set the button's text and center it within the button
void Button::setText(const string& text, const sf::Font& font, unsigned int characterSize) {
    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(characterSize);

    // Center the text on the button
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setPosition(
        position.x + (dimension.x - textBounds.width) / 2,
        position.y + (dimension.y - textBounds.height) / 2 - textBounds.top
    );
}

// Update button state based on mouse position and press state
void Button::update(const sf::Vector2f& mousePosition, bool isPressed) {
    // Check if the mouse is hovering over the button
    if (sprite.getGlobalBounds().contains(mousePosition)) {
        if (isPressed) {
            currentState = ButtonState::PRESSED;
            sprite.setTexture(pressedTexture);
            onClick();  // Trigger the button's onClick action
        } else {
            currentState = ButtonState::HOVER;
            sprite.setTexture(hoverTexture);
        }
    } else {
        currentState = ButtonState::NORMAL;
        sprite.setTexture(normalTexture);
    }
}

// Render the button
void Button::render(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(buttonText);  // Render the button text
}

// Check if the button is currently pressed
bool Button::isPressed() const {
    return currentState == ButtonState::PRESSED;
}

#include "InputManager.hpp"

/*
Class definition for InputManager, a class that manages input from the user.
*/

InputManager::InputManager() {}

// Singleton instance
InputManager& InputManager::getInstance() {
    static InputManager instance;
    return instance;
}

// Get the current mouse position
sf::Vector2i InputManager::getMousePosition(sf::RenderWindow& window) {
    return sf::Mouse::getPosition(window);
}

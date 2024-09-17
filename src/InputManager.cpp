#include "InputManager.hpp"

InputManager::InputManager() {}

InputManager& InputManager::getInstance() {
    static InputManager instance;
    return instance;
}

sf::Vector2i InputManager::getMousePosition(sf::RenderWindow& window) {
    return sf::Mouse::getPosition(window);
}

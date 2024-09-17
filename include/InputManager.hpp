#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <SFML/Graphics.hpp>

class InputManager {

public:
    static InputManager& getInstance();
    sf::Vector2i getMousePosition(sf::RenderWindow& window);

private:
    InputManager();
    InputManager(const InputManager&);
};

#endif // INPUTMANAGER_HPP
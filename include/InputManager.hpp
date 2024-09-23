#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <SFML/Graphics.hpp>

class InputManager {

public:
    static InputManager& getInstance();                             // Singleton pattern
    sf::Vector2i getMousePosition(sf::RenderWindow& window);        // Get the mouse position

private:
    InputManager();                                                 // Constructor
    InputManager(const InputManager&);                              // Copy constructor    
};

#endif // INPUTMANAGER_HPP
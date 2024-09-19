#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "MathHelper.hpp"
#include "Brick.hpp"
#include "Cannon.hpp"
#include "Bullet.hpp"
#include "LoadFromFile.hpp"

class GameManager {
public:
    GameManager();
    void run(); // Main game loop

private:
    sf::RenderWindow window;
    MathHelper mathHelper;
    LoadFromFile loadFromFile;
    Cannon cannon;
    std::vector<Bullet> bullets;
    std::vector<Brick> bricks;
    bool quit;

    sf::Clock clock;   // For tracking elapsed time
    sf::Text timerText; // For displaying the timer
    sf::Font font;      // Font for rendering text


    void handleEvents();           // Handle window events
    void updateGame();             // Update game logic
    void renderGame();             // Render the game
    void setupTimer();  
};

#endif

#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "LoadFromFile.hpp"
#include "SoundManager.hpp"
#include "MathHelper.hpp"
#include "Cannon.hpp"
#include "Bullet.hpp"
#include "Brick.hpp"
#include "Menu.hpp"
#include "Image.hpp"
#include <vector>
#include <iostream>
#include <iomanip>  // For formatting the timer
#include <sstream>  // For string manipulation
using namespace std;

class GameManager {
public:
    GameManager();
    void run(); // Main game loop

private:
    sf::RenderWindow window;
    MathHelper mathHelper;
    LoadFromFile loadFromFile;
    SoundManager soundManager;
    Cannon cannon;
    Menu menu;
    std::vector<Bullet> bullets;
    std::vector<Brick> bricks;
    bool quit;

    sf::Clock clock;   // For tracking elapsed time
    sf::Text timerText; // For displaying the timer
    sf::Font font;      // Font for rendering text
    vector<Image> walls;


    void handleEvents();           // Handle window events
    void updateGame();             // Update game logic
    void renderGame();             // Render the game
    void setupTimer();  
    void createWalls();
    void renderWalls(sf::RenderWindow& window);
    void startTimer();
};

#endif

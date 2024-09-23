#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "LoadFromFile.hpp"
#include "SoundManager.hpp"
#include "MathHelper.hpp"
#include "Cannon.hpp"
#include "Bullet.hpp"
#include "Button.hpp"
#include "Brick.hpp"
#include "Menu.hpp"
#include "Image.hpp"
#include <vector>
#include <iostream>
#include <iomanip>  
#include <sstream> 
using namespace std;

class GameManager {
public:
    GameManager();                                              // Constructor          
    void run();                                                 // Main game loop

private:                                                        // Member variables
    sf::RenderWindow window;
    MathHelper mathHelper;
    LoadFromFile loadFromFile;
    SoundManager soundManager;
    Cannon cannon;
    Menu menu;
    std::vector<Bullet> bullets;
    std::vector<Brick> bricks;
    bool quit;

    sf::Clock clock;   
    sf::Text timerText;
    sf::Font font;      
    vector<Image> walls;

    vector<Button> gameOverButtons;
    vector<Button> gameWinButtons;         
    bool gameOver = false;
    bool gameWin = false;
    void resetGame();

    void handleEvents();                                        // Handle window events
    void updateGame();             
    void renderGame();             
    void setupTimer();  
    void createWalls();
    void renderWalls(sf::RenderWindow& window);
    void startTimer();
    bool checkGameOver();
    bool checkGameWin();
    void renderGameOver();
    void renderGameWin();
};

#endif

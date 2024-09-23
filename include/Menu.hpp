#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.hpp"
#include "Image.hpp"
using namespace std;

class Menu {
public:
    Menu(sf::RenderWindow& window);                         // Constructor
    void handleEvents(sf::Event event);
    void update();
    void render();
    void drawMainMenu();
    void drawIntroMenu();
    void drawCreditsMenu();
    enum class GameState { IN_MENU, IN_GAME };              // Game state to switch between menus and game
    GameState gameState;
    bool continueClicked = false;
    enum class MenuState { MAIN_MENU};
    MenuState currentMenu;

private:
    sf::RenderWindow& window;                               // Member variables
    vector<Button> buttons;         
    vector<Button> buttonsIntro;    
    vector<Button> buttonsCredits;  
    vector<Image> images;               

    sf::Font font;  

    void setupMainMenu();                                   // Setup main menu
};

#endif // MENU_HPP

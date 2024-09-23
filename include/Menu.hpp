#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.hpp"
#include "Image.hpp"
using namespace std;

class Menu {
public:
    Menu(sf::RenderWindow& window);
    void handleEvents(sf::Event event);
    void update();
    void render();
    void drawMainMenu();
    void drawIntroMenu();
    void drawCreditsMenu();
    enum class GameState { IN_MENU, IN_GAME };  // Game state to switch between menus and game
    GameState gameState;
    bool continueClicked = false;
    enum class MenuState { MAIN_MENU};
    MenuState currentMenu;

private:


    sf::RenderWindow& window;
    vector<Button> buttons;         // Main menu buttons
    vector<Button> buttonsIntro;    // Intro menu buttons
    vector<Button> buttonsCredits;  // Credits menu buttons
    vector<Image> images;               

    sf::Font font;  // Font for button text

    void setupMainMenu();
};

#endif // MENU_HPP

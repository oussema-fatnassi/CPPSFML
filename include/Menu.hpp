#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.hpp"

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

private:
    enum class MenuState { MAIN_MENU, INTRO_MENU, CREDITS_MENU };

    MenuState currentMenu;

    sf::RenderWindow& window;
    std::vector<Button> buttons;         // Main menu buttons
    std::vector<Button> buttonsIntro;    // Intro menu buttons
    std::vector<Button> buttonsCredits;  // Credits menu buttons

    sf::Font font;  // Font for button text

    void setupMainMenu();
    void setupIntroMenu();
    void setupCreditsMenu();
};

#endif // MENU_HPP

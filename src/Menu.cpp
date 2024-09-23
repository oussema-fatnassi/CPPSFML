#include "Menu.hpp"
#include "AssetManager.hpp"
#include <iostream>

/*
Menu class is used to render the main menu of the game. It contains buttons for the user to interact with.
*/

Menu::Menu(sf::RenderWindow& window) : window(window), currentMenu(MenuState::MAIN_MENU) {
    // Load font for buttons
    if (!font.loadFromFile("../assets/fonts/Minecraft.ttf")) {
        std::cerr << "Error: could not load font Minecraft.ttf" << std::endl;
    }

    // Set up buttons for the main menu
    setupMainMenu();
}

// Set up the main menu buttons
void Menu::setupMainMenu() {
    buttons.clear();
    images.clear();

    images.emplace_back(sf::Vector2f(0, 0), sf::Vector2f(700, 900), "../assets/images/Background.png");
    images.emplace_back(sf::Vector2f(75,100), sf::Vector2f(550, 160), "../assets/images/MainMenu.png");

    // Start Button
    buttons.emplace_back(
        sf::Vector2f(200, 400), sf::Vector2f(300, 100),
        "../assets/images/button_normal.png", "../assets/images/button_hover.png", "../assets/images/button_pressed.png",
        [this]() {
            gameState = GameState::IN_GAME;  // Launch the game
            continueClicked = true;
        }
    );
    buttons.back().setText("START", font, 24);
    // Exit Button
    buttons.emplace_back(
        sf::Vector2f(200, 600), sf::Vector2f(300, 100),
        "../assets/images/button_normal.png", "../assets/images/button_hover.png", "../assets/images/button_pressed.png",
        [this]() {
            window.close();  // Exit the application
        }
    );
    buttons.back().setText("EXIT", font, 24);
}

// Handle user input events (mouse clicks)
void Menu::handleEvents(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        // Mouse click event, determine which menu we're in
        sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);

        switch (currentMenu) {
            case MenuState::MAIN_MENU:
                for (auto& button : buttons) {
                    button.update(mousePos, true);  // Handle button clicks
                }
                break;
            default:
                break;
        }
    }
}

// Update menu state, checking if the mouse is hovering over buttons
void Menu::update() {
    sf::Vector2f mousePos(sf::Mouse::getPosition(window));
    bool mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    // Update buttons based on the current menu state
    switch (currentMenu) {
        case MenuState::MAIN_MENU:
            for (auto& button : buttons) {
                button.update(mousePos, mousePressed);
            }
            break;
        default:
            break;
    }
}

// Render the appropriate menu
void Menu::render() {
    window.clear(sf::Color(255,255,255));
    
    // Render based on the current menu state
    switch (currentMenu) {
        case MenuState::MAIN_MENU:
            drawMainMenu();
            break;
        default:
            break;
    }
    window.display();
}

// Draw the main menu
void Menu::drawMainMenu() {
    for (auto& image : images) {
        image.render(window);
    }
    for (auto& button : buttons) {
        button.render(window);
    }
}

#include "Menu.hpp"
#include "AssetManager.hpp"
#include <iostream>

// Menu constructor
Menu::Menu(sf::RenderWindow& window) : window(window), currentMenu(MenuState::MAIN_MENU) {
    // Load font for buttons
    if (!font.loadFromFile("../assets/fonts/Minecraft.ttf")) {
        std::cerr << "Error: could not load font Minecraft.ttf" << std::endl;
    }

    // Set up buttons for the main menu
    setupMainMenu();
    setupIntroMenu();
    setupCreditsMenu();
}

// Set up the main menu buttons
void Menu::setupMainMenu() {
    buttons.clear();
    images.clear();

    images.emplace_back(sf::Vector2f(25,100), sf::Vector2f(550, 160), "../assets/images/MainMenu.png");

    // Start Button
    buttons.emplace_back(
        sf::Vector2f(200, 300), sf::Vector2f(200, 50),
        "../assets/images/button_normal.png", "../assets/images/button_hover.png", "../assets/images/button_pressed.png",
        [this]() {
            std::cout << "Start button clicked!" << std::endl;
            currentMenu = MenuState::INTRO_MENU;
        }
    );
    buttons.back().setText("START", font, 24);

    // Credits Button
    buttons.emplace_back(
        sf::Vector2f(200, 400), sf::Vector2f(200, 50),
        "../assets/images/button_normal.png", "../assets/images/button_hover.png", "../assets/images/button_pressed.png",
        [this]() {
            std::cout << "Credits button clicked!" << std::endl;
            currentMenu = MenuState::CREDITS_MENU;
        }
    );
    buttons.back().setText("CREDITS", font, 24);

    // Exit Button
    buttons.emplace_back(
        sf::Vector2f(200, 500), sf::Vector2f(200, 50),
        "../assets/images/button_normal.png", "../assets/images/button_hover.png", "../assets/images/button_pressed.png",
        [this]() {
            window.close();  // Exit the application
        }
    );
    buttons.back().setText("EXIT", font, 24);
}

// Set up the intro menu with the continue button
void Menu::setupIntroMenu() {
    buttonsIntro.clear();

    // Continue Button
    buttonsIntro.emplace_back(
        sf::Vector2f(200, 500), sf::Vector2f(200, 50),
        "../assets/images/button_normal.png", "../assets/images/button_hover.png", "../assets/images/button_pressed.png",
        [this]() {
            std::cout << "Continue button clicked!" << std::endl;
            gameState = GameState::IN_GAME;  // Launch the game
        }
    );
    buttonsIntro.back().setText("CONTINUE", font, 24);
}

// Set up the credits menu with the back button
void Menu::setupCreditsMenu() {
    buttonsCredits.clear();

    // Back Button
    buttonsCredits.emplace_back(
        sf::Vector2f(200, 700), sf::Vector2f(200, 50),
        "../assets/images/button_normal.png", "../assets/images/button_hover.png", "../assets/images/button_pressed.png",
        [this]() {
            std::cout << "Back button clicked!" << std::endl;
            currentMenu = MenuState::MAIN_MENU;  // Return to the main menu
        }
    );
    buttonsCredits.back().setText("BACK", font, 24);
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
            case MenuState::INTRO_MENU:
                for (auto& button : buttonsIntro) {
                    button.update(mousePos, true);
                }
                break;
            case MenuState::CREDITS_MENU:
                for (auto& button : buttonsCredits) {
                    button.update(mousePos, true);
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
        case MenuState::INTRO_MENU:
            for (auto& button : buttonsIntro) {
                button.update(mousePos, mousePressed);
            }
            break;
        case MenuState::CREDITS_MENU:
            for (auto& button : buttonsCredits) {
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
        case MenuState::INTRO_MENU:
            drawIntroMenu();
            break;
        case MenuState::CREDITS_MENU:
            drawCreditsMenu();
            break;
        default:
            break;
    }

    window.display();
}

// Draw the main menu
void Menu::drawMainMenu() {
    for (auto& button : buttons) {
        button.render(window);
    }
    for (auto& image : images) {
        image.render(window);
    }
}

// Draw the intro menu
void Menu::drawIntroMenu() {
    for (auto& button : buttonsIntro) {
        button.render(window);
    }
}

// Draw the credits menu
void Menu::drawCreditsMenu() {
    for (auto& button : buttonsCredits) {
        button.render(window);
    }
}

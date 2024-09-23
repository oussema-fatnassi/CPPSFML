#include "GameManager.hpp"

/*
Class definition for GameManager, a class that manages the game loop and game objects.
*/

GameManager::GameManager() 
    : window(sf::VideoMode(700, 900), "Breakout"), 
    loadFromFile("../assets/map/matrix.txt"),
    cannon(sf::Vector2f(350, 850), sf::Vector2f(150, 150), "../assets/images/Crossbow.png", &soundManager),
    quit(false), menu(window) {
    
    loadFromFile.loadGrid();
    loadFromFile.printGrid();
    bricks = loadFromFile.createBricks(soundManager);

    soundManager.loadSound("brick-crack", "../assets/sounds/brickCrack.ogg");
    soundManager.loadSound("ore-crack", "../assets/sounds/oreCrack.ogg");
    soundManager.loadSound("stone-crack", "../assets/sounds/stoneCrack.ogg");
    soundManager.loadSound("crossbow", "../assets/sounds/Crossbow.wav");
    soundManager.setVolume("crossbow", 30.f);

    // Load the font and setup the timer
    if (!font.loadFromFile("../assets/fonts/Minecraft.ttf")) {
        std::cerr << "Error: could not load font Minecraft.ttf" << std::endl;
    }
    setupTimer();

    createWalls();
}

void GameManager::setupTimer() {
    // Setup timer text properties
    timerText.setFont(font);
    timerText.setCharacterSize(40);            // Text size
    timerText.setFillColor(sf::Color::Black);  // Text color
    timerText.setPosition(50, 25);  // Position at bottom-left corner
}

// Main game loop
void GameManager::run() {
    while (window.isOpen()) {
        handleEvents();

        if (menu.gameState == Menu::GameState::IN_MENU) {
            menu.update();
            menu.render();
        } else if (menu.gameState == Menu::GameState::IN_GAME) {
            if (menu.continueClicked) {
                startTimer();                // Start or reset the timer
                menu.continueClicked = false; // Reset the flag to avoid repeated calls
            }
            updateGame();

            // Check if the game is over or won
            if (checkGameOver()) {
                if(!gameOver) {
                    gameOver = true;
                    menu.currentMenu = Menu::MenuState::MAIN_MENU;  // Return to main menu on game over
                    renderGameOver();  // Display Game Over screen
                }
            } else if (checkGameWin()) {
                if(!gameWin) {
                    gameWin = true;
                    menu.currentMenu = Menu::MenuState::MAIN_MENU;  // Return to main menu on game win
                    renderGameWin();  // Display Game Win screen
                }
            } else {
                renderGame();  // Continue rendering the game if not won or lost
            }
        }
        if (gameOver) {
            // Check hover and click detection for game over buttons
            sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
            bool mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

            for (auto& button : gameOverButtons) {
                button.update(mousePos, mousePressed); // Update hover and click states
            }
            
            renderGameOver();  // Render the game over screen and buttons
        } else if (gameWin) {
            // Check hover and click detection for game win buttons
            sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
            bool mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

            for (auto& button : gameWinButtons) {
                button.update(mousePos, mousePressed); // Update hover and click states
            }

        }
    }
}

// Handle window events
void GameManager::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            quit = true;
        }

        // Handle right-click to shoot
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left ) {
            bullets.push_back(cannon.shoot());
        }

        // Let the menu handle its own events when in the menu
        if (menu.gameState == Menu::GameState::IN_MENU) {
            menu.handleEvents(event);
        }
        // In the relevant section of handleEvents or main game loop
        if (menu.currentMenu == Menu::MenuState::MAIN_MENU) {
            gameOver = false;  // Reset game over state
            gameWin = false;   // Reset game win state
        }

    }
}

// Update game logic
void GameManager::updateGame() {
    cannon.updateRotation(window);

    // Update bullets and handle collisions
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        it->update(cannon.getPosition(), bricks, walls);
        if (!it->isActive()) {
            it = bullets.erase(it);
        } else {
            ++it;
        }
    }
    // Check game over or game win conditions
    if (checkGameOver()) {
        std::cout << "Game Over! Timer exceeded 1 minute." << std::endl;
        return;
    }

    if (checkGameWin()) {
        std::cout << "Game Win! All bricks destroyed." << std::endl;
        return;
    }
}

// Render the game
void GameManager::renderGame() {
    window.clear(sf::Color(251, 248, 239, 255));

    renderWalls(window);

    // Render trajectory, bricks, and cannon
    cannon.drawTrajectory(window);
    for (auto& brick : bricks) {
        brick.render(window);
    }
    cannon.render(window);

    // Render bullets
    for (auto& bullet : bullets) {
        bullet.render(window);
    }

    // Update the timer text
    sf::Time elapsed = clock.getElapsedTime();
    int totalSeconds = static_cast<int>(elapsed.asSeconds());
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    // Format the timer as MM:SS
    std::ostringstream timeStream;
    timeStream << std::setfill('0') << std::setw(2) << minutes << ":"
            << std::setfill('0') << std::setw(2) << seconds;
    timerText.setString(timeStream.str());

    // Draw the timer text
    window.draw(timerText);

    window.display();
}

void GameManager::createWalls() {
    // Top two layers of wall images
    for (int i = 0; i < 14; ++i) {
        walls.emplace_back(sf::Vector2f(i * 50, 0), sf::Vector2f(50, 50), "../assets/images/Wall.png");       // First top layer
        walls.emplace_back(sf::Vector2f(i * 50, 50), sf::Vector2f(50, 50), "../assets/images/Wall.png");      // Second top layer
    }

    // Left and right sides
    for (int i = 2; i < 17; ++i) {  // Start after top layers and end before bottom layers
        walls.emplace_back(sf::Vector2f(0, i * 50), sf::Vector2f(50, 50), "../assets/images/Wall.png");       // Left side
        walls.emplace_back(sf::Vector2f(650, i * 50), sf::Vector2f(50, 50), "../assets/images/Wall.png");     // Right side
    }

    // Bottom three layers
    for (int i = 0; i < 14; ++i) {
        walls.emplace_back(sf::Vector2f(i * 50, 850), sf::Vector2f(50, 50), "../assets/images/Wall.png");     // Third bottom layer
    }
}

void GameManager::renderWalls(sf::RenderWindow& window) {
    for (auto& wall : walls) {
        wall.render(window);  // Render each wall image
    }
}

void GameManager::startTimer() {
    clock.restart();      // Reset the timer clock
}

bool GameManager::checkGameOver() {
    sf::Time elapsed = clock.getElapsedTime();
    if (elapsed.asSeconds() >= 180 && !bricks.empty()) {
        std::cout << "Game Over! Timer exceeded 1 minute." << std::endl;
        return true;
    }
    return false;
}

bool GameManager::checkGameWin() {
    if (bricks.empty()) {
        std::cout << "You Win! All bricks destroyed." << std::endl;
        return true;
    }
    return false;
}

void GameManager::renderGameOver() {
    window.clear(sf::Color(0, 0, 0));  // Black background
    gameOverButtons.clear();  // Clear the buttons
    gameOverButtons.reserve(2);  // Reserve space for two buttons

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("Game Over!");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(200, 400);  // Centered

    gameOverButtons.emplace_back(
        sf::Vector2f(250, 700), sf::Vector2f(200, 50),
        "../assets/images/button_normal.png", "../assets/images/button_hover.png", "../assets/images/button_pressed.png",
        [this]() {
            std::cout << "Restart button clicked!" << std::endl;
            resetGame();  // Reset the game
        }
    );
    gameOverButtons.back().setText("RESTART", font, 24);
    gameOverButtons.emplace_back(
        sf::Vector2f(250, 800), sf::Vector2f(200, 50),
        "../assets/images/button_normal.png", "../assets/images/button_hover.png", "../assets/images/button_pressed.png",
        [this]() {
            std::cout << "Main Menu button clicked!" << std::endl;
            menu.currentMenu = Menu::MenuState::MAIN_MENU;  // Return to main menu
            menu.gameState = Menu::GameState::IN_MENU;  // Ensure the game state is set to the main menu
            gameOver = false;  // Reset game over state
        }
    );
    gameOverButtons.back().setText("MAIN MENU", font, 24);

    for (auto& button : gameOverButtons) {
        button.render(window);
    }

    window.draw(gameOverText);
    window.display();
}

void GameManager::renderGameWin() {
    window.clear(sf::Color(0, 0, 0));  // Black background
    gameWinButtons.clear();  // Clear the buttons
    gameWinButtons.reserve(1);  // Reserve space for one button

    sf::Text gameWinText;
    gameWinText.setFont(font);
    gameWinText.setString("You Win!");
    gameWinText.setCharacterSize(50);
    gameWinText.setFillColor(sf::Color::Green);
    gameWinText.setPosition(200, 400);  // Centered

    gameWinButtons.emplace_back(
        sf::Vector2f(250, 800), sf::Vector2f(200, 50),
        "../assets/images/button_normal.png", "../assets/images/button_hover.png", "../assets/images/button_pressed.png",
        [this]() {
            std::cout << "Main Menu button clicked!" << std::endl;
            resetGame();  // Reset the game
            menu.currentMenu = Menu::MenuState::MAIN_MENU;  // Return to main menu
            menu.gameState = Menu::GameState::IN_MENU;  // Ensure the game state is set to the main menu
            gameWin = false;  // Reset game over state
        }
    );
    gameWinButtons.back().setText("MAIN MENU", font, 24);

    for (auto& button : gameWinButtons) {
        button.render(window);
    }

    window.draw(gameWinText);
    window.display();
}

void GameManager::resetGame() {
    // Reset the timer
    startTimer();
    // Clear the current bullets
    bullets.clear();
    // Recreate the bricks from the loadFromFile object
    bricks = loadFromFile.createBricks(soundManager);
    // Reset game over flag and resume game state
    gameOver = false;
    gameWin = false;
    menu.gameState = Menu::GameState::IN_GAME;  // Resume the game
}

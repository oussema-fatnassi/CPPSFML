#include "GameManager.hpp"

/*
Class definition for GameManager, a class that manages the game loop and game objects.
*/

GameManager::GameManager() 
    : window(sf::VideoMode(700, 900), "Breakout"), 
    loadFromFile("../assets/map/matrix.txt"),
    cannon(sf::Vector2f(350, 850), sf::Vector2f(150, 150), "../assets/images/Crossbow.png"),
    quit(false), menu(window) {
    
    loadFromFile.loadGrid();
    loadFromFile.printGrid();
    bricks = loadFromFile.createBricks(soundManager);

    soundManager.loadSound("brick-crack", "../assets/sounds/brickCrack.ogg");
    soundManager.loadSound("ore-crack", "../assets/sounds/oreCrack.ogg");
    soundManager.loadSound("stone-crack", "../assets/sounds/stoneCrack.ogg");

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
            renderGame();
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
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right ) {
            bullets.push_back(cannon.shoot());
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


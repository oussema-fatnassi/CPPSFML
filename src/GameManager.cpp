#include "GameManager.hpp"
#include <iostream>
#include <iomanip>  // For formatting the timer
#include <sstream>  // For string manipulation

GameManager::GameManager() 
    : window(sf::VideoMode(600, 900), "Breakout"), 
    loadFromFile("../assets/map/matrix.txt"),
    cannon(sf::Vector2f(300, 900), sf::Vector2f(100, 200), "../assets/images/cannon.png"),
    quit(false) {
    
    loadFromFile.loadGrid();
    loadFromFile.printGrid();
    bricks = loadFromFile.createBricks();

    // Load the font and setup the timer
    if (!font.loadFromFile("../assets/fonts/ClearSansBold.ttf")) {
        std::cerr << "Error: could not load font ClearSansBold.ttf" << std::endl;
    }
    setupTimer();
}

void GameManager::setupTimer() {
    // Setup timer text properties
    timerText.setFont(font);
    timerText.setCharacterSize(24);            // Text size
    timerText.setFillColor(sf::Color::Black);  // Text color
    timerText.setPosition(10, window.getSize().y - 50);  // Position at bottom-left corner
}

void GameManager::run() {
    while (window.isOpen()) {
        handleEvents();
        updateGame();
        renderGame();
    }
}

void GameManager::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            quit = true;
        }

        // Handle right-click to shoot
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right && bullets.size() == 0) {
            bullets.push_back(cannon.shoot());
        }
    }
}

void GameManager::updateGame() {
    cannon.updateRotation(window);

    // Update bullets and handle collisions
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        it->update(cannon.getPosition(), bricks);
        if (!it->isActive()) {
            it = bullets.erase(it);
        } else {
            ++it;
        }
    }
}

void GameManager::renderGame() {
    window.clear(sf::Color(251, 248, 239, 255));

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

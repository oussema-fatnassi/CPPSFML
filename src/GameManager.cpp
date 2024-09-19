#include "GameManager.hpp"
#include <iostream>

GameManager::GameManager() 
    : window(sf::VideoMode(600, 900), "Breakout"), 
      loadFromFile("../assets/map/matrix.txt"),
      cannon(sf::Vector2f(300, 900), sf::Vector2f(100, 200), "../assets/images/cannon.png"),
      quit(false) {
    
    loadFromFile.loadGrid();
    loadFromFile.printGrid();
    bricks = loadFromFile.createBricks();
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

    window.display();
}

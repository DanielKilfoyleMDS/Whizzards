#include "PowerupManager.h"
#include <iostream>

PowerupManager::PowerupManager() {
    // Load the texture for the power-ups
    if (!powerUpTexture.loadFromFile("Resources/Textures/PowerUp.png")) {
        std::cerr << "Failed to load power-up texture!" << std::endl;
    }
}

void PowerupManager::initializePowerUps(const std::vector<sf::Vector2f>& spawnPoints) {
    // Loop through all the spawn points and create a power-up sprite for each
    for (const auto& point : spawnPoints) {
        spawnPowerUp(point);
    }
}

void PowerupManager::spawnPowerUp(const sf::Vector2f& position) {
    // Create a new sprite for the power-up and set its position
    sf::Sprite powerUp;
    powerUp.setTexture(powerUpTexture);
    powerUp.setPosition(position);
    powerUps.push_back(powerUp);
}

void PowerupManager::update(float deltaTime) {
    // Here you can add any logic that should run every frame (e.g., animation)
}

void PowerupManager::render(sf::RenderWindow& window) {
    // Draw all power-ups on the screen
    for (const auto& powerUp : powerUps) {
        window.draw(powerUp);
    }
}

void PowerupManager::collectPowerUp(const sf::Vector2f& playerPosition) {
    std::cout << "Player position: (" << playerPosition.x << ", " << playerPosition.y << ")" << std::endl;

    for (auto it = powerUps.begin(); it != powerUps.end();) {
        std::cout << "Power-up position: (" << it->getPosition().x << ", " << it->getPosition().y << ")" << std::endl;

        if (it->getGlobalBounds().contains(playerPosition)) {
            it = powerUps.erase(it);
            std::cout << "Power-up collected!" << std::endl;
        }
        else {
            ++it;
        }
    }
}


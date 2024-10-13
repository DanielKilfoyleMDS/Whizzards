#include "cWandManager.h"
#include <iostream>

cWandManager::cWandManager() {
    // Load the texture for the wands
    if (!wandTexture.loadFromFile("Resources/Textures/Wand.png")) {
        std::cerr << "Failed to load wand texture!" << std::endl;
    }
}

void cWandManager::initializeWands(const std::vector<sf::Vector2f>& spawnPoints) {
    // Loop through all the spawn points and create a wand sprite for each
    for (const auto& point : spawnPoints) {
        spawnWand(point);
    }
}

void cWandManager::spawnWand(const sf::Vector2f& position) {
    // Create a new sprite for the wand and set its position
    sf::Sprite wand;
    wand.setTexture(wandTexture);
    wand.setPosition(position);
    wands.push_back(wand);
}

void cWandManager::update(float deltaTime) {
    // Here you can add any logic that should run every frame (e.g., animation)
}

void cWandManager::render(sf::RenderWindow& window) {
    // Draw all wands on the screen
    for (const auto& wand : wands) {
        window.draw(wand);
    }
}

void cWandManager::collectWand(const sf::Vector2f& playerPosition) {
    // Check if the player collides with any wand
    for (auto it = wands.begin(); it != wands.end();) {
        if (it->getGlobalBounds().contains(playerPosition)) {
            // Wand collected, remove it from the list
            it = wands.erase(it);
            std::cout << "Wand collected!" << std::endl;
        }
        else {
            ++it;
        }
    }
}

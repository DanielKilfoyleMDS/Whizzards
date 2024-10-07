#include "PowerupManager.h"
#include "cPlayer.h"

PowerupManager::PowerupManager() {
    // Initialize the manager (e.g., initial powerups if needed)
}

void PowerupManager::update(float deltaTime) {
    for (auto& powerup : powerups) {
        powerup.update(deltaTime);  // Update each powerup
    }
}

void PowerupManager::draw(sf::RenderWindow& window) {
    for (auto& powerup : powerups) {
        powerup.draw(window);  // Draw each powerup
    }
}

void PowerupManager::spawnPowerup(WandType wandType, sf::Vector2f position) {
    powerups.push_back(Powerup(wandType, position));  // Add new powerup to the list
}

bool PowerupManager::checkCollision(cPlayer& player) {
    for (auto it = powerups.begin(); it != powerups.end();) {
        if (player.getBounds().intersects(it->getBounds())) {
            it->getWand().applyEffect(player);  // Apply the wand's effect to the player
            it = powerups.erase(it);  // Remove the powerup after it's picked up
            return true;  // Collision detected
        }
        else {
            ++it;
        }
    }
    return false;  // No collision detected
}

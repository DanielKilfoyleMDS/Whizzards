#pragma once
#include <vector>
#include "Powerup.h"

class PowerupManager {
public:
    PowerupManager();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void spawnPowerup(WandType wandType, sf::Vector2f position);
    bool checkCollision(class cPlayer& player);  // Check if player picks up a powerup

private:
    std::vector<Powerup> powerups;
};

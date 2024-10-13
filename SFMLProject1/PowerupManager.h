#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class PowerupManager {
public:
    PowerupManager();

    void initializePowerUps(const std::vector<sf::Vector2f>& spawnPoints);
    void update(float deltaTime);
    void render(sf::RenderWindow& window);

    void spawnPowerUp(const sf::Vector2f& position);
    void collectPowerUp(const sf::Vector2f& playerPosition);

private:
    std::vector<sf::Sprite> powerUps;
    sf::Texture powerUpTexture;
};

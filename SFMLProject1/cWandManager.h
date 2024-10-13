#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class cWandManager {
public:
    cWandManager();
    void initializeWands(const std::vector<sf::Vector2f>& spawnPoints);
    void spawnWand(const sf::Vector2f& position);
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    void collectWand(const sf::Vector2f& playerPosition);

private:
    sf::Texture wandTexture; // Texture for the wands
    std::vector<sf::Sprite> wands; // Vector to store wand sprites
};
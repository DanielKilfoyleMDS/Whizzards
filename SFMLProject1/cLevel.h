#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>

class cLevel {
public:
    cLevel(float width, float height);

    void LoadTileTextures(std::map<int, sf::Texture>& textures);
    bool LoadLevel(const std::string& filename, std::map<int, sf::Texture>& tileTextures, std::vector<std::vector<int>>& tileMap, std::vector<sf::Vector2f>& enemySpawnPoints, sf::Vector2f& player1Pos, sf::Vector2f& player2Pos);

    // New methods for level bounds
    float getLevelWidth() const; // Ensure return type is float
    float getLevelHeight() const; // Ensure return type is float
    sf::Vector2f getLevelCenter() const;

    // Check if a position is within level bounds
    bool isWithinBounds(const sf::Vector2f& position) const;

private:
    std::map<int, sf::Texture> tileTextures;
    sf::Vector2f levelCenter;
    float levelWidth;
    float levelHeight;

    std::vector<sf::Vector2f> LoadSpawnPoints(const std::string& filename);
};

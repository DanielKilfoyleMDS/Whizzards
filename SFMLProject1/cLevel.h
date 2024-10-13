#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>

class cLevel {
public:
    cLevel(float width, float height);

    void LoadTileTextures(std::map<int, sf::Texture>& textures);

    bool LoadLevel(const std::string& filename, const std::map<int, sf::Texture>& tileTextures, std::vector<std::vector<int>>& tileMap, std::vector<sf::Vector2f>& enemySpawnPoints, sf::Vector2f& player1Pos, sf::Vector2f& player2Pos);

    std::vector<sf::Vector2f> LoadSpawnPoints(const std::string& filename);

    bool isWithinBounds(const sf::Vector2f& position) const;

    // Getter methods
    float getLevelWidth() const;
    float getLevelHeight() const;
    sf::Vector2f getLevelCenter() const;


private:
  

    float levelWidth;
    float levelHeight;
    sf::Vector2f levelCenter;

    std::map<int, sf::Texture> tileTextures;
    std::vector<std::vector<int>> tileMap;

    std::vector<sf::Vector2f> wandSpawnPoints;
    std::vector<sf::Vector2f> powerUpSpawnPoints;
};
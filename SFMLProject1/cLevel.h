#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>

class cLevel {
public:
    cLevel(float width, float height);

    bool LoadLevel(const std::string& filename, const std::map<int, sf::Texture>& tileTextures, std::vector<std::vector<int>>& tileMap, std::vector<sf::Vector2f>& enemySpawnPoints, sf::Vector2f& player1Pos, sf::Vector2f& player2Pos);
    std::vector<sf::Vector2f> LoadSpawnPoints(const std::string& filename);

    float getLevelWidth() const;
    float getLevelHeight() const;
    sf::Vector2f getLevelCenter() const;

    std::vector<sf::Vector2f> getPowerUpSpawnPoints() const;

    bool isWithinBounds(const sf::Vector2f& position) const;

    void LoadTileTextures();  

    const std::map<int, sf::Texture>& getTileTextures() const {
        return tileTextures;
    }

private:
    float levelWidth;
    float levelHeight;
    sf::Vector2f levelCenter;

    std::map<int, sf::Texture> tileTextures;

    std::vector<sf::Vector2f> powerUpSpawnPoints;
    std::vector<sf::Vector2f> wandSpawnPoints;
};
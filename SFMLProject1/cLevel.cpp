#include "cLevel.h"
#include <fstream>
#include <iostream>
#include <sstream>

cLevel::cLevel(float width, float height) : levelWidth(width), levelHeight(height)
{
    levelCenter = sf::Vector2f(1500.f, 1500.f);
    LoadTileTextures(tileTextures);
}

void cLevel::LoadTileTextures(std::map<int, sf::Texture>& textures)
{
    if (!textures[1].loadFromFile("Resources/Textures/Grass.png"))
    {
        std::cerr << "Failed to load grass texture!" << std::endl;
    }
    if (!textures[2].loadFromFile("Resources/Textures/Sand.png"))
    {
        std::cerr << "Failed to load sand texture!" << std::endl;
    }
    if (!textures[3].loadFromFile("Resources/Textures/Water.png"))
    {
        std::cerr << "Failed to load water texture!" << std::endl;
    }
    if (!textures[4].loadFromFile("Resources/Textures/Path.png"))
    {
        std::cerr << "Failed to load path texture!" << std::endl;
    }
}

bool cLevel::LoadLevel(const std::string& filename, const std::map<int, sf::Texture>& tileTextures, std::vector<std::vector<int>>& tileMap, std::vector<sf::Vector2f>& enemySpawnPoints, sf::Vector2f& player1Pos, sf::Vector2f& player2Pos)
{
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open level file!" << std::endl;
        return false;
    }

    std::string line;
    int y = 0;
    while (std::getline(file, line))
    {
        std::vector<int> row;
        for (char tile : line) {
            if (tile == 'G') {
                row.push_back(1); // Grass
            }
            else if (tile == 'S') {
                row.push_back(2); // Sand
            }
            else if (tile == 'W') {
                wandSpawnPoints.emplace_back(y * 64, row.size() * 64);
            }
            else if (tile == 'P') {
                powerUpSpawnPoints.emplace_back(y * 64, row.size() * 64);
            }
            else {
                row.push_back(0);
            }
        }
        tileMap.push_back(row);
        y++;
    }

    levelWidth = tileMap[0].size() * 64;
    levelHeight = tileMap.size() * 64;
    levelCenter = sf::Vector2f(levelWidth / 2.0f, levelHeight / 2.0f);

    file.close();
    return true;
}

std::vector<sf::Vector2f> cLevel::LoadSpawnPoints(const std::string& filename)
{
    std::vector<sf::Vector2f> spawnPoints;
    std::ifstream file(filename);

    if (!file)
    {
        std::cerr << "Failed to open spawn points file!" << std::endl;
        return spawnPoints;
    }

    float x, y;
    while (file >> x >> y)
    {
        spawnPoints.emplace_back(x, y);
    }

    return spawnPoints;
}

bool cLevel::isWithinBounds(const sf::Vector2f& position) const
{
    return position.x >= 0 && position.x <= levelWidth && position.y >= 0 && position.y <= levelHeight;
}

// Getter methods
float cLevel::getLevelWidth() const
{
    return levelWidth;
}

float cLevel::getLevelHeight() const
{
    return levelHeight;
}

sf::Vector2f cLevel::getLevelCenter() const
{
    return levelCenter;
}

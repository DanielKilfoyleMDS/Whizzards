#include "cLevel.h"
#include <fstream>
#include <iostream>
#include <sstream>

cLevel::cLevel(float width, float height):levelWidth(width), levelHeight(height) 
{
    // Initialize level bounds (example values)
    levelCenter = sf::Vector2f(1500.f, 1500.f); // Set to center of your level
    levelWidth = 3000.f; // Width of your level
    levelHeight = 3000.f; // Height of your level

    // Load the textures
    LoadTileTextures(tileTextures); // Pass only the texture map
}

void cLevel::LoadTileTextures(std::map<int, sf::Texture>& textures) {
    if (!textures[1].loadFromFile("Resources/Textures/Grass.png")) {
        std::cerr << "Failed to load grass texture!" << std::endl;
    }
    if (!textures[2].loadFromFile("Resources/Textures/Sand.png")) {
        std::cerr << "Failed to load sand texture!" << std::endl;
    }
}

bool cLevel::LoadLevel(const std::string& filename, std::map<int, sf::Texture>& tileTextures, std::vector<std::vector<int>>& tileMap, std::vector<sf::Vector2f>& enemySpawnPoints, sf::Vector2f& player1Pos, sf::Vector2f& player2Pos) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open level file!" << std::endl;
        return false;
    }

    std::string line;
    int y = 0;
    while (std::getline(file, line)) {
        std::vector<int> row;
        for (char tile : line) {
            if (tile == 'G') {
                row.push_back(1); // Grass
            }
            else if (tile == 'S') {
                row.push_back(2); // Sand
            }
            else {
                row.push_back(0); // Empty tile or others
            }
        }
        tileMap.push_back(row);
        y++;
    }

    // Set the level dimensions
    levelWidth = tileMap[0].size() * 64; // Assuming 64 is the tile width
    levelHeight = tileMap.size() * 64; // Assuming 64 is the tile height
    levelCenter = sf::Vector2f(levelWidth / 2.0f, levelHeight / 2.0f);

    // Load enemy spawn points
    enemySpawnPoints = LoadSpawnPoints("Resources/Levels/spawn_points.txt");

    // Close the level file
    file.close();
    return true;
}

std::vector<sf::Vector2f> cLevel::LoadSpawnPoints(const std::string& filename) {
    std::vector<sf::Vector2f> spawnPoints;
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Failed to open spawn points file!" << std::endl;
        return spawnPoints;
    }

    float x, y;
    while (file >> x >> y) {
        spawnPoints.emplace_back(x, y);
    }

    return spawnPoints;
}

bool cLevel::isWithinBounds(const sf::Vector2f& position) const {
    return position.x >= 0 && position.x <= levelWidth && position.y >= 0 && position.y <= levelHeight;
}

// Getter methods
float cLevel::getLevelWidth() const {
    return levelWidth;
}

float cLevel::getLevelHeight() const {
    return levelHeight;
}

sf::Vector2f cLevel::getLevelCenter() const {
    return sf::Vector2f(levelWidth / 2, levelHeight / 2);
}
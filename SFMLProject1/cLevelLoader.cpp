#include "cLevelLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

cLevelLoader::cLevelLoader()
{
    // Load the textures
    if (!grassTex.loadFromFile("Resources/Textures/Grass.png"))
    {
        std::cerr << "Failed to load grass texture!" << std::endl;
    }

    if (!sandTex.loadFromFile("Resources/Textures/Sand.png"))
    {
        std::cerr << "Failed to load sand texture!" << std::endl;
    }

    // Load new textures for Water and Path
    if (!waterTex.loadFromFile("Resources/Textures/Water.png"))
    {
        std::cerr << "Failed to load water texture!" << std::endl;
    }

    if (!pathTex.loadFromFile("Resources/Textures/Path.png"))
    {
        std::cerr << "Failed to load path texture!" << std::endl;
    }
}

bool cLevelLoader::LoadLevel(const std::string& filename, sf::Sprite& map, sf::Vector2f& player1Pos, sf::Vector2f& player2Pos,
    std::vector<sf::Vector2f>& wandSpawnPoints, std::vector<sf::Vector2f>& powerUpSpawnPoints) {
    std::string fullPath = "Resources/Levels/" + filename;
    std::ifstream file(fullPath);
    if (!file.is_open()) {
        std::cerr << "Failed to open level file: " << fullPath << std::endl;
        return false;
    }

    std::string line;
    int y = 0; // Track the row number for positioning tiles
    while (std::getline(file, line)) {
        auto tokens = SplitString(line, ' ');

        if (tokens.empty())
            continue;  // Skip empty lines

        if (tokens[0] == "PLAYER1") {
            if (tokens.size() < 3) {
                std::cerr << "Invalid PLAYER1 line format" << std::endl;
                return false;
            }
            player1Pos = sf::Vector2f(std::stof(tokens[1]), std::stof(tokens[2]));
        }
        else if (tokens[0] == "PLAYER2") {
            if (tokens.size() < 3) {
                std::cerr << "Invalid PLAYER2 line format" << std::endl;
                return false;
            }
            player2Pos = sf::Vector2f(std::stof(tokens[1]), std::stof(tokens[2]));
        }
        else {
            // Process tiles for the current row
            for (int x = 0; x < tokens.size(); ++x) {
                sf::Sprite tile;
                if (tokens[x] == "1") { // Grass tile
                    tile.setTexture(grassTex);
                }
                else if (tokens[x] == "2") { // Sand tile
                    tile.setTexture(sandTex);
                }
                else if (tokens[x] == "W") { // Wand spawn
                    wandSpawnPoints.emplace_back(x * 64, y * 64); // Store the spawn point
                }
                else if (tokens[x] == "P") { // Power-up spawn
                    powerUpSpawnPoints.emplace_back(x * 64, y * 64); // Store the spawn point
                }
                else {
                    std::cerr << "Invalid tile type in level file: " << tokens[x] << std::endl;
                    continue;
                }

                // Set tile position based on grid coordinates
                tile.setPosition(x * 64, y * 64); // Assuming each tile is 64x64 pixels

                // Render the tile to the map (or you can store these tiles in a vector to render later)
                map = tile; // Replace this with adding tiles to your game world
            }
            y++; // Move to the next row
        }
    }

    file.close();
    return true;
}


std::vector<std::string> cLevelLoader::SplitString(const std::string& str, char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }

    return tokens;
}

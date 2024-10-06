#include "cLevelLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

cLevelLoader::cLevelLoader() {}

bool cLevelLoader::LoadLevel(const std::string& filename, sf::Sprite& map, sf::Vector2f& player1Pos, sf::Vector2f& player2Pos, std::vector<sf::Vector2f>& enemyPositions)
{
    std::string fullPath = "Resources/Levels/" + filename;
    std::ifstream file(fullPath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open level file: " << fullPath << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line))
    {
        auto tokens = SplitString(line, ' ');

        if (tokens.empty())
            continue;  // Skip empty lines

        if (tokens[0] == "MAP")
        {
            if (tokens.size() < 2)
            {
                std::cerr << "Invalid MAP line format" << std::endl;
                return false;
            }

            // Use the class member mapTex
            if (!mapTex.loadFromFile(tokens[1]))
            {
                std::cerr << "Failed to load map texture: " << tokens[1] << std::endl;
                return false;
            }
            map.setTexture(mapTex);
        }
        else if (tokens[0] == "PLAYER1")
        {
            if (tokens.size() < 3)
            {
                std::cerr << "Invalid PLAYER1 line format" << std::endl;
                return false;
            }

            player1Pos = sf::Vector2f(std::stof(tokens[1]), std::stof(tokens[2]));
        }
        else if (tokens[0] == "PLAYER2")
        {
            if (tokens.size() < 3)
            {
                std::cerr << "Invalid PLAYER2 line format" << std::endl;
                return false;
            }

            player2Pos = sf::Vector2f(std::stof(tokens[1]), std::stof(tokens[2]));
        }
        else if (tokens[0] == "ENEMY")
        {
            if (tokens.size() < 3)
            {
                std::cerr << "Invalid ENEMY line format" << std::endl;
                return false;
            }

            enemyPositions.push_back(sf::Vector2f(std::stof(tokens[1]), std::stof(tokens[2])));
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

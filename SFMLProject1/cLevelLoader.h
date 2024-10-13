#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class cLevelLoader
{
public:
    cLevelLoader();
    bool LoadLevel(const std::string& filename, sf::Sprite& map, sf::Vector2f& player1Pos, sf::Vector2f& player2Pos,
        std::vector<sf::Vector2f>& wandSpawnPoints, std::vector<sf::Vector2f>& powerUpSpawnPoints);

private:
    std::vector<std::string> SplitString(const std::string& str, char delimiter);
    sf::Texture grassTex;  // Grass texture
    sf::Texture sandTex;   // Sand texture
    sf::Texture pathTex;  // Declare pathTex
    sf::Texture waterTex; // Declare waterTex
};

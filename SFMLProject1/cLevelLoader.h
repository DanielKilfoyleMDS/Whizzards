#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class cLevelLoader
{
public:
    cLevelLoader();
    bool LoadLevel(const std::string& filename, sf::Sprite& map, sf::Vector2f& player1Pos, sf::Vector2f& player2Pos, std::vector<sf::Vector2f>& enemyPositions);

private:
    std::vector<std::string> SplitString(const std::string& str, char delimiter);
    sf::Texture mapTex;  // Declare mapTex here as a class member
};

/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : cLevel.cpp
Description : 
Author : Jandre Cronje
**************************************************************************/
#include "cLevel.h"
#include <fstream>
#include <iostream>
#include <sstream>

cLevel::cLevel(float width, float height) : m_flevelWidth(width), m_flevelHeight(height)
{
    m_levelCenter = sf::Vector2f(1500.f, 1500.f);
    loadTileTextures();  
}

void cLevel::loadTileTextures()
{
    if (!m_tileTextures[1].loadFromFile("Resources/Textures/Grass.png"))
    {
        std::cerr << "Failed to load grass texture!" << std::endl;
    }
    if (!m_tileTextures[2].loadFromFile("Resources/Textures/Sand.png"))
    {
        std::cerr << "Failed to load sand texture!" << std::endl;
    }
    if (!m_tileTextures[3].loadFromFile("Resources/Textures/Wand.png"))
    {
        std::cerr << "Failed to load water texture!" << std::endl;
    }

}

bool cLevel::LoadLevel(const std::string& filename, const std::map<int, sf::Texture>& tileTextures, std::vector<std::vector<int>>& tileMap,
    const std::string& _Spawnpointfilename, sf::Vector2f& player1Pos, sf::Vector2f& player2Pos, const std::string& _wandSpawnsfilename)
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
                m_wandSpawnPoints.emplace_back(y * 64, row.size() * 64);
            }
            else {
                row.push_back(0);
            }
        }
        tileMap.push_back(row);
        y++;
    }

    m_flevelWidth = tileMap[0].size() * 64;
    m_flevelHeight = tileMap.size() * 64;
    m_levelCenter = sf::Vector2f(m_flevelWidth / 2.0f, m_flevelHeight / 2.0f);

    m_enemySpawnPoints = LoadSpawnPoints(_Spawnpointfilename);
    m_wandSpawnPoints = LoadSpawnPoints(_wandSpawnsfilename);

    file.close();
    return true;
}

std::vector<sf::Vector2f> cLevel::LoadSpawnPoints(const std::string& filename)
{
    std::vector<sf::Vector2f> spawnPoints;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open spawn points file: " << filename << std::endl;
        return spawnPoints;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        float x, y;
        char comma; // To skip the comma if you have a comma-separated format

        // Assuming the spawn points are in the format: x,y
        if (iss >> x >> comma >> y) // Read x and y values
        {
            spawnPoints.emplace_back(x, y); // Store the spawn point
            std::cout << "Loaded spawn point: (" << x << ", " << y << ")" << std::endl; // Debug output
        }
        else
        {
            std::cerr << "Invalid line format in spawn points file: " << line << std::endl; // Handle parsing errors
        }
    }

    file.close();
    std::cout << "Finished loading spawn points. Total spawn points loaded: " << spawnPoints.size() << std::endl;

    return spawnPoints;
}

bool cLevel::isWithinBounds(const sf::Vector2f& position) const
{
    return position.x >= 0 && position.x <= m_flevelWidth && position.y >= 0 && position.y <= m_flevelHeight;
}

// Getter methods
float cLevel::getLevelWidth() const
{
    return m_flevelWidth;
}

float cLevel::getLevelHeight() const
{
    return m_flevelHeight;
}

sf::Vector2f cLevel::getLevelCenter() const
{
    return m_levelCenter;
}


std::vector<sf::Vector2f> cLevel::getPowerUpSpawnPoints() const {
    return m_powerUpSpawnPoints;
}

std::vector<sf::Vector2f>* cLevel::getEnemySpawnPoints()
{
    return &m_enemySpawnPoints;
}

std::vector<sf::Vector2f>* cLevel::getWandSpawnPoints()
{
    return &m_wandSpawnPoints;
}

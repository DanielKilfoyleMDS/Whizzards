/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : cLevel.h
Description : Main program for Whizzards Game
Author : Jandre Cronje
**************************************************************************/
#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>

class cLevel {
public:
    cLevel(float width, float height);

    bool LoadLevel(const std::string& filename, const std::map<int, sf::Texture>& tileTextures, std::vector<std::vector<int>>& tileMap, const std::string& _Spawnpointfilename, sf::Vector2f& player1Pos, sf::Vector2f& player2Pos);
    std::vector<sf::Vector2f> LoadSpawnPoints(const std::string& filename);

    float getLevelWidth() const;
    float getLevelHeight() const;
    sf::Vector2f getLevelCenter() const;

    std::vector<sf::Vector2f> getPowerUpSpawnPoints() const;

    std::vector<sf::Vector2f>* getEnemySpawnPoints();

    bool isWithinBounds(const sf::Vector2f& position) const;

    void loadTileTextures();  



    const std::map<int, sf::Texture>& getTileTextures() const {
        return m_tileTextures;
    }

private:
    float m_flevelWidth;
    float m_flevelHeight;
    sf::Vector2f m_levelCenter;

    std::map<int, sf::Texture> m_tileTextures;

    std::vector<sf::Vector2f> m_powerUpSpawnPoints;
    std::vector<sf::Vector2f> m_wandSpawnPoints;
    std::vector<sf::Vector2f> m_enemySpawnPoints;

};
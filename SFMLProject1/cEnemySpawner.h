#pragma once
#include "cEnemyPool.h"
#include <SFML/System.hpp>
#include <vector>
#include <string>
#include <iostream>

class cEnemySpawner {
public:
    void LoadSpawnPoints(const std::string& filename);
    cEnemySpawner(int _basePoints, int _wavePointGain, cEnemyPool* _Pool);
    ~cEnemySpawner();

    bool SpawnEnemy(sf::Vector2f position); // Declaration should match
    void WaveManager();

private:
    std::vector<sf::Vector2f> m_SpawnPoints; // List of spawn points

    int m_icurrentPoints;
    int m_icurrentWave;
    int m_ibasePoints;
    int m_iwavePointGain;
    cEnemyPool* m_EnemyPoolRef;

    int m_imaxEnemiesAtOnce;
    int m_imaxEnemiesInWave;

    int CalculateWavePoints();
    void StartWave();
    //bool SpawnEnemy(); // Method to spawn enemy without parameters

    bool SpawnAsteroidEnemy(sf::Vector2f spawnPosition);
    bool SpawnRandomEnemy(sf::Vector2f spawnPosition);
};

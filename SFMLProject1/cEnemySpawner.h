/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : cEnemySpawner.h
Description : Enemy Spawner for Whizzards Game
Author : Jayden Burns
Mail : JaydenBurns@mds.ac.nz
**************************************************************************/
#pragma once
#include "cEnemyPool.h"

class cEnemySpawner
{
public:
	cEnemySpawner(int _basePoints, int _wavePointGain, cEnemyPool* _Pool, class cPlayer* _PlayerOne, class cPlayer* _PlayerTwo);
	cEnemySpawner(int _basePoints, int _wavePointGain, cEnemyPool* _Pool, int _enemiesOnScreen, int _enemiesTotal, class cPlayer* _PlayerOne, class cPlayer* _PlayerTwo);
	~cEnemySpawner();

	void setSpawnPoints(std::vector<sf::Vector2f>* _spawnpoints);

	void WaveManager(float _deltaTime, cScore& score, cLevel _level);
	
private:

	int m_icurrentPoints;
	int m_icurrentWave;
	int m_ibasePoints;
	int m_iwavePointGain;
	cEnemyPool* m_EnemyPoolRef;

	int m_imaxEnemiesAtOnce;
	int m_imaxEnemiesInWave;

	std::vector<sf::Vector2f>* m_spawnPoints = nullptr;

	class cPlayer* m_playerOne;
	class cPlayer* m_playerTwo;
	float m_fsafeSpawnRange = 300;


	int calculateWavePoints();
	void startWave();
	bool spawnEnemy();

	sf::Vector2f chooseSpawnPoint();

	bool isSpawnPointSafe(sf::Vector2f _spawnpoint);

	bool spawnRandomEnemy(sf::Vector2f _position);
	bool spawnAsteroidEnemy(sf::Vector2f _position);
	bool spawnChaseEnemy(sf::Vector2f _position);
	bool spawnShootEnemy(sf::Vector2f _position);
	


};


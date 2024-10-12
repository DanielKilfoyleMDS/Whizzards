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
	cEnemySpawner(int _basePoints, int _wavePointGain, cEnemyPool* _Pool);
	cEnemySpawner(int _basePoints, int _wavePointGain, cEnemyPool* _Pool, int _enemiesOnScreen, int _enemiesTotal);
	~cEnemySpawner();

	void WaveManager();

private:

	int m_icurrentPoints;
	int m_icurrentWave;
	int m_ibasePoints;
	int m_iwavePointGain;
	cEnemyPool* m_EnemyPoolRef;

	int m_imaxEnemiesAtOnce;
	int m_imaxEnemiesInWave;

	int calculateWavePoints();
	void startWave();
	bool spawnEnemy();

	bool spawnRandomEnemy();
	bool spawnAsteroidEnemy();
	bool spawnChaseEnemy();
	

};


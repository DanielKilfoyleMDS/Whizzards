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

	int CalculateWavePoints();
	void StartWave();
	bool SpawnEnemy();

	bool SpawnRandomEnemy();
	bool SpawnAsteroidEnemy();

	

};


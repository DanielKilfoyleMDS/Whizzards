#pragma once
#include "cEnemyPool.h"

class cEnemySpawner
{
public:
	cEnemySpawner(int _basePoints, int _wavePointGain, cEnemyPool* _Pool);
	~cEnemySpawner();

	void WaveManager();

private:

	int m_currentPoints;
	int m_currentWave;
	int m_basePoints;
	int m_wavePointGain;
	int CalculateWavePoints();
	void StartWave();

	cEnemyPool* m_EnemyPoolRef;

};


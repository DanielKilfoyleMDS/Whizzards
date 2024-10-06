#include "cEnemySpawner.h"
#include "MathLibrary.h"

cEnemySpawner::cEnemySpawner(int _basePoints, int _wavePointGain, cEnemyPool* _Pool)
{
	m_currentWave = 0;
	m_wavePointGain = _wavePointGain;
	m_basePoints = _basePoints;
	m_currentPoints = CalculateWavePoints();

	m_EnemyPoolRef = _Pool;
}

cEnemySpawner::~cEnemySpawner()
{
}

void cEnemySpawner::WaveManager()
{
	if (m_EnemyPoolRef->GetActiveEnemies().size() == 0)
	{
		m_currentWave++;
		StartWave();
	}
}


int cEnemySpawner::CalculateWavePoints()
{
	return m_basePoints + (m_currentWave * m_wavePointGain);
}

void cEnemySpawner::StartWave()
{
	m_currentPoints = CalculateWavePoints();
	int EnemyChoice = 0;
	while (m_currentPoints > 0)
	{
		EnemyChoice = randRangeInt(0,1);
		
		if (EnemyChoice == 1 && m_currentPoints >= 2)
		{
			//Version 1
			m_EnemyPoolRef->loadRandomEnemy(sf::Vector2f(0,0));
			m_currentPoints -= 2;
		}
		else if (EnemyChoice == 0)
		{
			m_EnemyPoolRef->loadAsteroidEnemy(sf::Vector2f((float)randRangeInt(-20, 20), 0), sf::Vector2f(1,1),1);
			m_currentPoints -= 1;
		}
	}
}

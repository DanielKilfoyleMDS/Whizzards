#include "cEnemySpawner.h"
#include "MathLibrary.h"

cEnemySpawner::cEnemySpawner(int _basePoints, int _wavePointGain, cEnemyPool* _Pool)
{
	m_icurrentWave = 0;
	m_iwavePointGain = _wavePointGain;
	m_ibasePoints = _basePoints;
	m_icurrentPoints = CalculateWavePoints();

	m_EnemyPoolRef = _Pool;
	m_imaxEnemiesAtOnce = m_EnemyPoolRef->GetInactiveEnemies().size();
	m_imaxEnemiesInWave = m_imaxEnemiesAtOnce * 2;

}

cEnemySpawner::cEnemySpawner(int _basePoints, int _wavePointGain, cEnemyPool* _Pool, int _enemiesOnScreen, int _enemiesTotal)
{
	m_icurrentWave = 0;
	m_iwavePointGain = _wavePointGain;
	m_ibasePoints = _basePoints;
	m_icurrentPoints = CalculateWavePoints();

	m_EnemyPoolRef = _Pool;
	m_imaxEnemiesAtOnce = _enemiesOnScreen;
	m_imaxEnemiesInWave = _enemiesTotal;
}

cEnemySpawner::~cEnemySpawner()
{
}

void cEnemySpawner::WaveManager()
{
	m_EnemyPoolRef->tickEnemies();

	//Check if there are no enemies left on screen
	if (m_EnemyPoolRef->GetActiveEnemies().size() == 0)
	{
		m_icurrentWave++;
		std::cout << "StartingWave" << std::endl;
		StartWave();
	}
	
	//Check if there are still points to spawn and room for another enemy
	if (m_icurrentPoints > 0 && m_EnemyPoolRef->GetActiveEnemies().size() < m_imaxEnemiesAtOnce) 
	{
		//Spawning additional enemies per wave can go here - BETA SPRINT GOAL
	}

}


int cEnemySpawner::CalculateWavePoints()
{
	int Points = m_ibasePoints + (m_icurrentWave * m_iwavePointGain);
	if (Points > m_imaxEnemiesAtOnce * 2) //Set to highest cost enemy - maybe make these const member variables
	{
		Points = m_imaxEnemiesAtOnce * 2;
	}
	return Points;
}

void cEnemySpawner::StartWave()
{
	m_icurrentPoints = CalculateWavePoints();
	int EnemiesSpawned = 0;
	bool CanSpawn = true;
	while (CanSpawn)
	{
		if (m_icurrentPoints > 0 && m_EnemyPoolRef->GetActiveEnemies().size() < m_imaxEnemiesAtOnce)
		{
			CanSpawn = SpawnEnemy(); //Returns false if enemy spawning fails
		}
		else CanSpawn = false;
	}
}

bool cEnemySpawner::SpawnEnemy()
{
	int EnemyChoice = 0;
	EnemyChoice = randRangeInt(0, 1);
	if (EnemyChoice == 0 && m_icurrentPoints >= 1)
	{
		return SpawnAsteroidEnemy();
	} else if (EnemyChoice == 1 && m_icurrentPoints >= 2)
	{
		return SpawnRandomEnemy();
	}
	else if (m_icurrentPoints <= 0)
	{
		return false;
	}
	else {
		std::cout << "Reroll" << std::endl;
		return SpawnEnemy(); //If we reach this point, we still have points to spend.
	}
	
}

bool cEnemySpawner::SpawnRandomEnemy()
{
	return m_EnemyPoolRef->loadRandomEnemy(sf::Vector2f(0, 0));
}

bool cEnemySpawner::SpawnAsteroidEnemy()
{
	return m_EnemyPoolRef->loadAsteroidEnemy(sf::Vector2f((float)randRangeInt(-20, 20), 0), sf::Vector2f(1, 1), 1);
}

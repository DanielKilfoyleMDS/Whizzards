/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : cEnemySpawner.cpp
Description : Enemy Spawner for Whizzards Game
Author : Jayden Burns
Mail : JaydenBurns@mds.ac.nz
**************************************************************************/
#include "cEnemySpawner.h"
#include "MathLibrary.h"

/************************************************************************
Name: cEnemySpawner
Description : Constructor for Enemy Spawner. Sets Max values based on Pool Size
Parameters: int _basePoints, int _wavePointGain, cEnemyPool* _Pool
Returns: None
Author : Jayden Burns
**************************************************************************/
cEnemySpawner::cEnemySpawner(int _basePoints, int _wavePointGain, cEnemyPool* _Pool)
{
	m_icurrentWave = 0;
	m_iwavePointGain = _wavePointGain;
	m_ibasePoints = _basePoints;
	m_icurrentPoints = CalculateWavePoints();

	m_EnemyPoolRef = _Pool;
	m_imaxEnemiesAtOnce = m_EnemyPoolRef->getInactiveEnemies().size();
	m_imaxEnemiesInWave = m_imaxEnemiesAtOnce * 2;

}

/************************************************************************
Name: cEnemySpawner
Description : Constructor for Enemy Spawner. Sets Max values based on Constructor
Parameters: int _basePoints, int _wavePointGain, cEnemyPool* _Pool, int _enemiesOnScreen, int _enemiesTotal
Returns: None
Author : Jayden Burns
**************************************************************************/
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

/************************************************************************
Name: ~cEnemyPool
Description : Deconstructor for Enemyspawner.
Parameters: None
Returns: None
Author : Jayden Burns
**************************************************************************/
cEnemySpawner::~cEnemySpawner()
{
	m_EnemyPoolRef = nullptr;
}

/************************************************************************
Name: WaveManager
Description : Checks to see if wave is complete, starts new wave.
Parameters: None
Returns: None
Author : Jayden Burns
**************************************************************************/
void cEnemySpawner::WaveManager()
{
	m_EnemyPoolRef->tickEnemies();

	//Check if there are no enemies left on screen
	if (m_EnemyPoolRef->getActiveEnemies().size() == 0)
	{
		m_icurrentWave++;
		std::cout << "StartingWave" << std::endl;
		StartWave();
	}
	
	//Check if there are still points to spawn and room for another enemy
	if (m_icurrentPoints > 0 && m_EnemyPoolRef->getActiveEnemies().size() < m_imaxEnemiesAtOnce) 
	{
		//Spawning additional enemies per wave can go here - BETA SPRINT GOAL
	}

}

/************************************************************************
Name: CalculateWavePoints
Description : Calculates Points based on current wave, point gain, and max enemies.
Parameters: None
Returns: int (Number of Points)
Author : Jayden Burns
**************************************************************************/
int cEnemySpawner::CalculateWavePoints()
{
	//TODO - Improve math for this function
	int Points = m_ibasePoints + (m_icurrentWave * m_iwavePointGain);
	if (Points > m_imaxEnemiesAtOnce * 2) //Set to highest cost enemy - maybe make these const member variables
	{
		Points = m_imaxEnemiesAtOnce * 2;
	}
	return Points;
}

/************************************************************************
Name: StartWave
Description : Starts Next Wave
Parameters: None
Returns: None
Author : Jayden Burns
**************************************************************************/
void cEnemySpawner::StartWave()
{
	m_icurrentPoints = CalculateWavePoints();
	int EnemiesSpawned = 0;
	bool CanSpawn = true;
	while (CanSpawn)
	{
		if (m_icurrentPoints > 0 && m_EnemyPoolRef->getActiveEnemies().size() < m_imaxEnemiesAtOnce)
		{
			CanSpawn = SpawnEnemy(); //Returns false if enemy spawning fails
		}
		else CanSpawn = false;
	}
}

/************************************************************************
Name: SpawnEnemy
Description : Chooses Enemy to Spawn and subtracts the point cost
Parameters: None
Returns: bool - false if unsuccessful
Author : Jayden Burns
**************************************************************************/
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
		return SpawnEnemy(); //If we reach this point, we still have points to spend.
	}
	
}

/************************************************************************
Name: SpawnRandomEnemy
Description : Spawns Random Type Enemy
Parameters: None
Returns: bool - false if unsuccessful
Author : Jayden Burns
**************************************************************************/
bool cEnemySpawner::SpawnRandomEnemy()
{
	return m_EnemyPoolRef->loadRandomEnemy(sf::Vector2f(0, 0));
}

/************************************************************************
Name: SpawnAsteroidEnemy
Description : Spawns Asteroid Type Enemy
Parameters: None
Returns: bool - false if unsuccessful
Author : Jayden Burns
**************************************************************************/
bool cEnemySpawner::SpawnAsteroidEnemy()
{
	return m_EnemyPoolRef->loadAsteroidEnemy(sf::Vector2f((float)randRangeInt(-20, 20), 0), sf::Vector2f(1, 1), 1);
}

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
#include "cLevel.h"
#include "MathLibrary.h"
#include "cScore.h"


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
	m_icurrentPoints = calculateWavePoints();

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
	m_icurrentPoints = calculateWavePoints();

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
Name: setSpawnPoints
Description : sets SpawnPoints used by spawner
Parameters: std::vector<sf::Vector2f>* _spawnpoints
Returns: None
Author : Jayden Burns
**************************************************************************/
void cEnemySpawner::setSpawnPoints(std::vector<sf::Vector2f>* _spawnpoints)
{
	m_spawnPoints = _spawnpoints;
}

/************************************************************************
Name: WaveManager
Description : Checks to see if wave is complete, starts new wave.
Parameters: None
Returns: None
Author : Jayden Burns
**************************************************************************/
void cEnemySpawner::WaveManager(float _deltaTime, cScore& score, cLevel _level)
{
	m_EnemyPoolRef->tickEnemies(_deltaTime, score, _level);


	//Check if there are no enemies left on screen
	if (m_EnemyPoolRef->getActiveEnemies().size() == 0)
	{
		m_icurrentWave++;
		std::cout << "StartingWave" << m_icurrentWave << std::endl;
		startWave();
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
int cEnemySpawner::calculateWavePoints()
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
void cEnemySpawner::startWave()
{
	m_icurrentPoints = calculateWavePoints();
	std::cout << "Starting Points" << m_icurrentPoints << std::endl;
	int EnemiesSpawned = 0;
	bool CanSpawn = true;
	while (CanSpawn)
	{
		if (m_icurrentPoints > 0 && m_EnemyPoolRef->getActiveEnemies().size() < m_imaxEnemiesAtOnce)
		{
			std::cout << "Current Points" << m_icurrentPoints << std::endl;
			CanSpawn = spawnEnemy(); //Returns false if enemy spawning fails
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
bool cEnemySpawner::spawnEnemy()
{
	int iEnemyChoice = randRangeInt(0, 4);
	sf::Vector2f SpawnPosition = sf::Vector2f(0,0);
	if (m_spawnPoints != nullptr && m_spawnPoints->size() > 0)
	{
		if (m_spawnPoints->size() > 1)
		{
			int ispawnPointChoice = randRangeInt(0, m_spawnPoints->size() - 1);
			SpawnPosition = (*m_spawnPoints)[ispawnPointChoice];
		}
		else if (m_spawnPoints->size() == 1)
		{
			SpawnPosition = (*m_spawnPoints)[0];
		}
	}

	
	if (iEnemyChoice == 0 && m_icurrentPoints >= 1)
	{
		if (spawnAsteroidEnemy(SpawnPosition))
		{
			m_icurrentPoints -= 1;
			return true;
		}
		else return false;
	} else if (iEnemyChoice == 1 && m_icurrentPoints >= 2)
	{
		if (spawnRandomEnemy(SpawnPosition))
		{
			m_icurrentPoints -= 2;
			return true;
		}
		else return false;
	}
	else if (iEnemyChoice == 2 && m_icurrentPoints >= 2)
	{
		if (spawnChaseEnemy(SpawnPosition))
		{
			m_icurrentPoints -= 2;
			return true;
		}else return false;
	}
	else if (iEnemyChoice == 3 && m_icurrentPoints >= 5)
	{
		if (spawnShootEnemy(SpawnPosition))
		{
			m_icurrentPoints -= 2;
			return true;
		} else return false;
	}
	else if (m_icurrentPoints <= 0)
	{
		return false;
	}
	else {
		return spawnEnemy(); //If we reach this point, we still have points to spend.
	}
	
}

/************************************************************************
Name: spawnRandomEnemy
Description : Spawns Random Type Enemy
Parameters: None
Returns: bool - false if unsuccessful
Author : Jayden Burns
**************************************************************************/
bool cEnemySpawner::spawnRandomEnemy(sf::Vector2f _position)
{

	return m_EnemyPoolRef->loadRandomEnemy(_position);
}

/************************************************************************
Name: spawnAsteroidEnemy
Description : Spawns Asteroid Type Enemy
Parameters: None
Returns: bool - false if unsuccessful
Author : Jayden Burns
**************************************************************************/
bool cEnemySpawner::spawnAsteroidEnemy(sf::Vector2f _position)
{
	return m_EnemyPoolRef->loadAsteroidEnemy(_position, sf::Vector2f(1, 1), 1);
}

/************************************************************************
Name: spawnChaseEnemy
Description : Spawns Chase Type Enemy
Parameters: None
Returns: bool - false if unsuccessful
Author : Jayden Burns
**************************************************************************/
bool cEnemySpawner::spawnChaseEnemy(sf::Vector2f _position)
{
	return m_EnemyPoolRef->loadChaseEnemy(_position);
}

bool cEnemySpawner::spawnShootEnemy(sf::Vector2f _position)
{
	return m_EnemyPoolRef->loadShootEnemy(_position);
}

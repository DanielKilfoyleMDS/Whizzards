/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : cEnemyPool.cpp
Description : Enemy Pool for Whizzards Game
Author : Jayden Burns
Mail : JaydenBurns@mds.ac.nz
**************************************************************************/
#include "cEnemyPool.h"

/************************************************************************
Name: cEnemyPool
Description : Constructor for Enemy Pool
Parameters: int _enemyCount, sf::Sprite* _defaultSprite, std::vector<cCharacter*>* _collisionVector
Returns: None
Author : Jayden Burns
**************************************************************************/
cEnemyPool::cEnemyPool(int _enemyCount, sf::Sprite* _defaultSprite, std::vector<cCharacter*>* _collisionVector)
{
	//TODO - Add Additional Sprites

	m_DefaultSprite = _defaultSprite;

	for (int i = 0; i < _enemyCount; i++)
	{
		//Position should be set to out of map location, 0 0 for now

		cEnemy* Enemy = new cEnemy(_defaultSprite, sf::Vector2f(0, 0));
		m_enemiesInactive.push_back(Enemy);
		_collisionVector->push_back(Enemy);
	}
}

/************************************************************************
Name: ~cEnemyPool
Description : Deconstructor for Enemy Pool
Parameters: int _enemyCount, sf::Sprite* _defaultSprite, std::vector<cCharacter*>* _collisionVector
Returns: None
Author : Jayden Burns
**************************************************************************/
cEnemyPool::~cEnemyPool()
{
	//Sprites are cleared by Game Manager
	m_AsteroidSprite = nullptr;
	m_DefaultSprite = nullptr;

	//TODO - communicate with gamemanager to clear enemies from list
	//Maybe this needs a ref to game manager, could also be used for getting sprites
}


/************************************************************************
Name: loadAsteroidEnemy
Description : Loads first available enemy as an Asteroid Enemy
Parameters: sf::Vector2f _position, sf::Vector2f _movement, float _speed
Returns: bool - false if unsuccessful
Author : Jayden Burns
**************************************************************************/
bool cEnemyPool::loadAsteroidEnemy(sf::Vector2f _position, sf::Vector2f _movement, float _speed)
{
	//TODO - Debug mode printout active/inactive
	//TODO - Add Sprite code

	if (m_enemiesInactive.size() > 0)
	{
		cEnemy* Asteroid = m_enemiesInactive[0];
		m_enemiesActive.push_back(Asteroid);
		m_enemiesInactive.erase(m_enemiesInactive.begin());

		Asteroid->setPosition(_position);
		//Asteroid->setSprite();
		Asteroid->setMovement(_movement);
		Asteroid->setHealth(10); //TODO get variables from gamemanager not hardcoded
		Asteroid->setState(Idle);
		Asteroid->setAwake(true);
		Asteroid->setBehaviour(&m_AsteroidBehaviour);
		m_AsteroidBehaviour.pickDirection(Asteroid);
		Asteroid->setDamageStrength(1);
		return true;
	} 
	return false;
}

/************************************************************************
Name: loadRandomEnemy
Description : Loads first available enemy as a Random Type Enemy
Parameters: sf::Vector2f _position
Returns: bool - false if unsuccessful
Author : Jayden Burns
**************************************************************************/
bool cEnemyPool::loadRandomEnemy(sf::Vector2f _position)
{
	//TODO - Add Sprite code
	if (m_enemiesInactive.size() > 0)
	{
		cEnemy* Random = m_enemiesInactive[0];
		m_enemiesActive.push_back(Random);
		m_enemiesInactive.erase(m_enemiesInactive.begin());

		Random->setPosition(_position);
		Random->setHealth(10);

		Random->setState(Idle);
		Random->setAwake(true);
		Random->setBehaviour(&m_RandomBehaviour);
		Random->setDamageStrength(2);
		return true;
	}

	return false;
}

/************************************************************************
Name: tickEnemies
Description : iterates through all active enemies, runs their tick behaviour, and unloads inactive enemies
Parameters: None
Returns: None
Author : Jayden Burns
**************************************************************************/
void cEnemyPool::tickEnemies()
{
	for (int EnemyCount = 0; EnemyCount < m_enemiesActive.size(); EnemyCount++)
	{
		cEnemy* Enemy = m_enemiesActive[EnemyCount];
		Enemy->tick();

		if (Enemy->getAwake() != true)
		{
			//If the current enemy has been set to be asleep, it is "Dead"
			//So we unload it
			m_enemiesActive.erase(m_enemiesActive.begin() + EnemyCount);

			m_enemiesInactive.push_back(Enemy);
		}
	}
}

/************************************************************************
Name: getActiveEnemies
Description : Gets Active Enemy List
Parameters: None
Returns: std::vector<cEnemy*> m_enemiesActive
Author : Jayden Burns
**************************************************************************/
std::vector<cEnemy*> cEnemyPool::getActiveEnemies()
{
	return m_enemiesActive;
}

/************************************************************************
Name: getInactiveEnemies
Description : Gets Inactive Enemy List
Parameters: None
Returns: std::vector<cEnemy*> m_enemiesInactive
Author : Jayden Burns
**************************************************************************/
std::vector<cEnemy*> cEnemyPool::getInactiveEnemies()
{
	return m_enemiesInactive;
}

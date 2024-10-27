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

	if (m_enemiesInactive.size() > 0)
	{
		cEnemy* Asteroid = m_enemiesInactive[0];
		m_enemiesActive.push_back(Asteroid);
		m_enemiesInactive.erase(m_enemiesInactive.begin());

		m_AsteroidBehaviour.setupEnemy(Asteroid, _position);
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
	if (m_enemiesInactive.size() > 0)
	{
		cEnemy* Random = m_enemiesInactive[0];
		m_enemiesActive.push_back(Random);
		m_enemiesInactive.erase(m_enemiesInactive.begin());

		m_RandomBehaviour.setupEnemy(Random, _position);
		return true;
	}

	return false;
}

/************************************************************************
Name: loadChaseEnemy
Description : Loads first available enemy as a Chase Type Enemy
Parameters: sf::Vector2f _position
Returns: bool - false if unsuccessful
Author : Jayden Burns
**************************************************************************/
bool cEnemyPool::loadChaseEnemy(sf::Vector2f _position)
{
	if (m_enemiesInactive.size() > 0)
	{
		cEnemy* Chase = m_enemiesInactive[0];
		m_enemiesActive.push_back(Chase);
		m_enemiesInactive.erase(m_enemiesInactive.begin());

		m_ChaseBehaviour.setupEnemy(Chase, _position);
		return true;
	}
	return false;
}

/************************************************************************
Name: loadShootEnemy
Description : Loads first available enemy as a Shoot Type Enemy
Parameters: sf::Vector2f _position
Returns: bool - false if unsuccessful
Author : Jayden Burns
**************************************************************************/
bool cEnemyPool::loadShootEnemy(sf::Vector2f _position)
{
	if (m_enemiesInactive.size() > 0)
	{
		cEnemy* Shoot = m_enemiesInactive[0];
		m_enemiesActive.push_back(Shoot);
		m_enemiesInactive.erase(m_enemiesInactive.begin());

		m_ShootBehaviour.setupEnemy(Shoot, _position);
		return true;
	}
	return false;
}

/************************************************************************
Name: setPlayers
Description : Passes Players into all behaviours that require player references
Parameters: cCharacter* _player1, cCharacter* _player2
Returns: none
Author : Jayden Burns
**************************************************************************/
void cEnemyPool::setPlayers(cCharacter* _player1, cCharacter* _player2)
{
	if (_player2 == nullptr)
	{
		m_ChaseBehaviour.setPlayers(_player1);
	}
	else
	{
		m_ChaseBehaviour.setPlayers(_player1, _player2);
	}
}

/************************************************************************
Name: tickEnemies
Description : iterates through all active enemies, runs their tick behaviour, and unloads inactive enemies
Parameters: None
Returns: None
Author : Jayden Burns
**************************************************************************/
void cEnemyPool::tickEnemies(float _deltaTime)
{
	for (int EnemyCount = 0; EnemyCount < m_enemiesActive.size(); EnemyCount++)
	{
		cEnemy* Enemy = m_enemiesActive[EnemyCount];
		Enemy->tick(_deltaTime);

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

/************************************************************************
Name: setBehaviourSprites
Description : Sets Sprites used by Enemy Behaviours
Parameters: sf::Sprite* _AsteroidSprite, sf::Sprite* _RandomSprite,  sf::Sprite* _chaseSprite
Returns: None
Author : Jayden Burns
**************************************************************************/
void cEnemyPool::setBehaviourSprites(sf::Sprite* _asteroidSprite, sf::Sprite* _randomSprite, sf::Sprite* _chaseSprite)
{
	m_AsteroidBehaviour.setBehaviourSprite(_asteroidSprite);
	m_RandomBehaviour.setBehaviourSprite(_randomSprite);
	m_ChaseBehaviour.setBehaviourSprite(_chaseSprite);
}


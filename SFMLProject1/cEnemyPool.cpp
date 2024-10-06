#include "cEnemyPool.h"

cEnemyPool::cEnemyPool(int _enemyCount)
{
	for (int i = 0; i < _enemyCount; i++)
	{
		//Position should be set to out of map location, 0 0 for now
		cEnemy* Enemy = new cEnemy("Resources/Textures/Sprites/EnemyDefault.png", "Enemy", sf::Vector2f(0, 0));
		m_enemiesInactive.push_back(Enemy);
	}
}

cEnemyPool::~cEnemyPool()
{
}

//TODO - return bool
//TODO - Debug mode printout active/inactive
bool cEnemyPool::loadAsteroidEnemy(sf::Vector2f _position, sf::Vector2f _movement, float _speed)
{
	if (m_enemiesInactive.size() > 0)
	{
		cEnemy* Asteroid = m_enemiesInactive[0];
		m_enemiesActive.push_back(Asteroid);
		m_enemiesInactive.erase(m_enemiesInactive.begin());

		Asteroid->SetPosition(_position);
		//Asteroid->setSprite();
		Asteroid->setMovement(_movement);
		Asteroid->setHealth(10); //TODO get variables from gamemanager not hardcoded
		Asteroid->setState(Idle);
		Asteroid->setAwake(true);
		Asteroid->setBehaviour(&m_AsteroidBehaviour);
		return true;
	} 
	return false;
}

bool cEnemyPool::loadRandomEnemy(sf::Vector2f _position)
{
	if (m_enemiesInactive.size() > 0)
	{
		cEnemy* Asteroid = m_enemiesInactive[0];
		m_enemiesActive.push_back(Asteroid);
		m_enemiesInactive.erase(m_enemiesInactive.begin());

		Asteroid->SetPosition(_position);
		Asteroid->setHealth(10);

		Asteroid->setState(Idle);
		Asteroid->setAwake(true);
		Asteroid->setBehaviour(&m_RandomBehaviour);
		return true;
	}

	return false;
}

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
			m_enemiesActive.erase(m_enemiesInactive.begin() + EnemyCount - 1);
			m_enemiesInactive.push_back(Enemy);
			
		}
	}
}


std::vector<cEnemy*> cEnemyPool::GetActiveEnemies()
{
	return m_enemiesActive;
}

std::vector<cEnemy*> cEnemyPool::GetInactiveEnemies()
{
	return m_enemiesInactive;
}

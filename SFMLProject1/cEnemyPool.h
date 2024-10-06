#pragma once
#include "cEnemy.h"
#include "cAsteroidBehaviour.h"
#include "cRandomBehaviour.h"
class cEnemyPool
{
public:
	cEnemyPool(int _enemyCount);
	~cEnemyPool();

	bool loadAsteroidEnemy(sf::Vector2f _position, sf::Vector2f _movement, float _speed);
	bool loadRandomEnemy(sf::Vector2f _position);

	void tickEnemies();

	std::vector<cEnemy*> GetActiveEnemies();
	std::vector<cEnemy*> GetInactiveEnemies();


private:
	std::vector<cEnemy*> m_enemiesInactive;
	std::vector<cEnemy*> m_enemiesActive;

	cAsteroidBehaviour m_AsteroidBehaviour;
	cRandomBehaviour m_RandomBehaviour;
};


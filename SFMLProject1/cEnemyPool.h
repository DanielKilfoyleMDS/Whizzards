#pragma once
#include "cEnemy.h"
#include "cAsteroidBehaviour.h"
class cEnemyPool
{
public:
	cEnemyPool(int _enemyCount);
	~cEnemyPool();

	void LoadAsteroidEnemy(sf::Vector2f _position, sf::Vector2f _movement, float _speed);

	std::vector<cEnemy*> GetActiveEnemies();
	std::vector<cEnemy*> GetInactiveEnemies();


private:
	std::vector<cEnemy*> m_enemiesInactive;
	std::vector<cEnemy*> m_enemiesActive;

	cAsteroidBehaviour m_AsteroidBehaviour;
};


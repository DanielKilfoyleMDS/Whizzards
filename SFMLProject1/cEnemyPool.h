#pragma once
#include "cEnemy.h"
#include "cEnemyDrift.h"
class cEnemyPool
{
public:
	cEnemyPool(int EnemyCount);
	~cEnemyPool();

	int GetInactiveEnemyCount();
	int GetActiveEnemyCount();

	void LoadAsteroidEnemy(sf::Vector2f _Position, sf::Vector2f Direction, float Speed);

private:
	std::vector<cEnemy*> Enemies_Inactive;
	std::vector<cEnemy*> Enemies_Active;

	cEnemyDrift m_DriftBehaviour;
};


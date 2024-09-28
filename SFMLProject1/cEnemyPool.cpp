#include "cEnemyPool.h"

cEnemyPool::cEnemyPool(int EnemyCount)
{
	for (int i = 0; i < EnemyCount; i++)
	{
		//Position should be set to out of map location, 0 0 for now
		cEnemy* Enemy = new cEnemy("Resources/Textures/Sprites/EnemyDefault","Enemy",sf::Vector2f(0,0));
		Enemies_Inactive.push_back(Enemy);
	}
}

cEnemyPool::~cEnemyPool()
{
}

int cEnemyPool::GetInactiveEnemyCount()
{
	return Enemies_Inactive.size();
}

int cEnemyPool::GetActiveEnemyCount()
{
	return Enemies_Active.size();
}

void cEnemyPool::LoadAsteroidEnemy(sf::Vector2f _Position, sf::Vector2f Direction, float Speed)
{
	//Grab First Enemy in chain
}

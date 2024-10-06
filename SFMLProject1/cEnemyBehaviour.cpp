#include "cEnemyBehaviour.h"
#include "cEnemy.h"

cEnemyBehaviour::cEnemyBehaviour()
{
}

cEnemyBehaviour::~cEnemyBehaviour()
{
}

bool cEnemyBehaviour::TickEnemy(cEnemy* _parent)
{
	return false;
}

bool cEnemyBehaviour::CheckDeath(cEnemy* _parent)
{
	if (_parent->getHealth() < 1)
	{
		return true;
	}
	return false;
}

bool cEnemyBehaviour::CanAttack(cEnemy* _parent)
{
	return false;
}

void cEnemyBehaviour::Attack(cEnemy* _parent)
{
}

void cEnemyBehaviour::Move(cEnemy* _parent)
{
}

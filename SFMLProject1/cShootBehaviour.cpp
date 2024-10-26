#include "cShootBehaviour.h"

cShootBehaviour::cShootBehaviour()
{
}

cShootBehaviour::~cShootBehaviour()
{
}

bool cShootBehaviour::tickEnemy(cEnemy* _parent, float _deltaTime)
{
	return false;
}

bool cShootBehaviour::checkDeath(cEnemy* _parent)
{
	return false;
}

bool cShootBehaviour::canAttack(cEnemy* _parent)
{
	return false;
}

void cShootBehaviour::enemyAttack(cEnemy* _parent)
{
}

void cShootBehaviour::enemyMove(cEnemy* _parent)
{
}

#include "cFollowBehaviour.h"

cFollowBehaviour::~cFollowBehaviour()
{
}

bool cFollowBehaviour::tickEnemy(cEnemy* _parent, float _deltaTime)
{
	return false;
}

bool cFollowBehaviour::checkDeath(cEnemy* _parent)
{
	return false;
}

bool cFollowBehaviour::canAttack(cEnemy* _parent)
{
	return false;
}

void cFollowBehaviour::enemyAttack(cEnemy* _parent)
{
}

void cFollowBehaviour::enemyMove(cEnemy* _parent)
{
}

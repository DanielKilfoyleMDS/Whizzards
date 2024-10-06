#include "cFollowBehaviour.h"

cFollowBehaviour::~cFollowBehaviour()
{
}

bool cFollowBehaviour::TickEnemy(cEnemy* _parent)
{
	return false;
}

bool cFollowBehaviour::CheckDeath(cEnemy* _parent)
{
	return false;
}

bool cFollowBehaviour::CanAttack(cEnemy* _parent)
{
	return false;
}

void cFollowBehaviour::Attack(cEnemy* _parent)
{
}

void cFollowBehaviour::Move(cEnemy* _parent)
{
}

#include "cRandomBehaviour.h"
#include "cEnemy.h"
#include <iostream>
#include "MathLibrary.h"

cRandomBehaviour::cRandomBehaviour()
{
}

cRandomBehaviour::~cRandomBehaviour()
{
}

bool cRandomBehaviour::TickEnemy(cEnemy* _parent)
{
	Move(_parent);

	if (CheckDeath(_parent))
	{
		return false;
	}
	return true;
}

bool cRandomBehaviour::CheckDeath(cEnemy* _parent)
{
	if (_parent->getHealth() < 1)
	{
		return true;
	}
	return false;
}

bool cRandomBehaviour::CanAttack(cEnemy* _parent)
{
	return false;
}

void cRandomBehaviour::Attack(cEnemy* _parent)
{
}

void cRandomBehaviour::Move(cEnemy* _parent)
{
	if (_parent->getMoveTime() > 0)
	{
		sf::Vector2f NewPosition = _parent->getPosition() + _parent->getMovement();
		_parent->SetPosition(NewPosition);
		//I guess we decrease movetime in enemy tick to put in deltatime
	}
	else
	{
		PickDirection(_parent);
	}
}

void cRandomBehaviour::PickDirection(cEnemy* _parent)
{
	//CONCEPT WORKS, REDO RAND
	float RandXDirection = randRangeFloat(-1,1);
	float RandYDirection = randRangeFloat(-1, 1);

	float Movetime = 5 * randRangeFloat(0,20);
	_parent->setMoveTime(Movetime);
	_parent->setMovement(sf::Vector2f(RandXDirection, RandYDirection));


	//Randomly picks a direction (-1 to 1)
	//Also randomly picks a movetime
}

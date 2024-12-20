/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : cRandomBehaviour.cpp
Description : Behaviour class for Random wander enemy
Author : Jayden Burns
Mail : JaydenBurns@mds.ac.nz
**************************************************************************/
#include "cRandomBehaviour.h"
#include "cEnemy.h"
#include <iostream>
#include "MathLibrary.h"

/************************************************************************
Name: cRandomBehaviour
Description : constructor for Random Behaviour Class
Parameters: None
Returns: None
Author : Jayden Burns
**************************************************************************/
cRandomBehaviour::cRandomBehaviour()
{
}

/************************************************************************
Name: ~cRandomBehaviour
Description : deconstructor for Random Behaviour Class
Parameters: None
Returns: None
Author : Jayden Burns
**************************************************************************/
cRandomBehaviour::~cRandomBehaviour()
{
}

/************************************************************************
Name: tickEnemy
Description : runs random behaviour on enemy.
Parameters: cEnemy* _parent
Returns: bool - false if unsuccessful.
Author : Jayden Burns
**************************************************************************/
bool cRandomBehaviour::tickEnemy(cEnemy* _parent, float _deltaTime)
{
	enemyMove(_parent);

	_parent->setFrame(_parent->getFrame() + _parent->framesPassed(_deltaTime));
	if (_parent->getFrame() > 3)
	{
		_parent->setFrame(0);
	}

	if (checkDeath(_parent))
	{
		return false;
	}
	return true;
}

/************************************************************************
Name: checkDeath
Description : checks if enemy should be dead.
Parameters: cEnemy* _parent
Returns: bool - true if it should be dead
Author : Jayden Burns
**************************************************************************/
bool cRandomBehaviour::checkDeath(cEnemy* _parent)
{
	if (_parent->getHealth() < 1)
	{
		return true;
	}
	return false;
}

/************************************************************************
Name: canAttack
Description : checks if enemy canAttack.
Parameters: cEnemy* _parent
Returns: bool - true if can Attack
Author : Jayden Burns
**************************************************************************/
bool cRandomBehaviour::canAttack(cEnemy* _parent)
{
	return false;
}


/************************************************************************
Name: enemyAttack
Description : runs attack behaviour of enemy. 
Parameters: cEnemy* _parent
Returns: None
Author : Jayden Burns
**************************************************************************/
void cRandomBehaviour::enemyAttack(cEnemy* _parent)
{
}

/************************************************************************
Name: enemyMove
Description : runs move behaviour of enemy.
Parameters: cEnemy* _parent
Returns: None
Author : Jayden Burns
**************************************************************************/
void cRandomBehaviour::enemyMove(cEnemy* _parent)
{
	if (_parent->getMoveTime() > 0)
	{
		sf::Vector2f NewPosition = _parent->getPosition() + _parent->getMovement();
		_parent->setRotation(vectorRotationAngle(_parent->getMovement()));
		_parent->setPosition(NewPosition);
	}
	else
	{
		pickDirection(_parent);
	}
}

void cRandomBehaviour::setupEnemy(cEnemy* _parent, sf::Vector2f _position)
{
	_parent->setPosition(_position);
	_parent->setHealth(7);
	_parent->setEnemyType(Type_Random);
	_parent->setState(Idle);
	_parent->setAwake(true);
	_parent->setBehaviour(this);
	_parent->setDamageStrength(2);
}

/************************************************************************
Name: pickDirection
Description : picks which direction to move towards
Parameters: cEnemy* _parent
Returns: None
Author : Jayden Burns
**************************************************************************/
void cRandomBehaviour::pickDirection(cEnemy* _parent)
{
	float RandXDirection = randRangeFloat(-1,1);
	float RandYDirection = randRangeFloat(-1, 1);

	float Movetime = 5 * randRangeFloat(20,60);
	_parent->setMoveTime(Movetime);
	_parent->setMovement(sf::Vector2f(RandXDirection * 1.5, RandYDirection * 1.5));
}

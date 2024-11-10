/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : cAsteroidBehaviour.cpp
Description : Behaviour class for Asteroid enemy
Author : Jayden Burns
Mail : JaydenBurns@mds.ac.nz
**************************************************************************/
#include "cAsteroidBehaviour.h"
#include "cEnemy.h"

/************************************************************************
Name: cAsteroidBehaviour
Description : constructor for Asteroid Behaviour Class
Parameters: None
Returns: None
Author : Jayden Burns
**************************************************************************/
cAsteroidBehaviour::cAsteroidBehaviour()
{

}

/************************************************************************
Name: ~cAsteroidBehaviour
Description : deconstructor for Asteroid Behaviour Class
Parameters: None
Returns: None
Author : Jayden Burns
**************************************************************************/
cAsteroidBehaviour::~cAsteroidBehaviour()
{
}

/************************************************************************
Name: tickEnemy
Description : runs tick behaviour on enemy.
Parameters: cEnemy* _parent
Returns: bool - false if unsuccessful.
Author : Jayden Burns
**************************************************************************/
bool cAsteroidBehaviour::tickEnemy(cEnemy* _parent, float _deltaTime)
{
	_parent->setFrame(_parent->getFrame() + _parent->framesPassed(_deltaTime));
	if (_parent->getFrame() > 0)
	{
		_parent->setFrame(0);
	}

	_parent->setRotation(_parent->getRotation() + _deltaTime * 5);

	if (_parent != nullptr)
	{
		if (_parent->getAwake())
		{
			//Logic - Asteroid can only drift.
			switch (_parent->getState())
			{
			case Idle:
				enemyMove(_parent);
				break;
			default:
				_parent->setState(Idle);
				break;
			}
		}
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
bool cAsteroidBehaviour::checkDeath(cEnemy* _parent)
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
bool cAsteroidBehaviour::canAttack(cEnemy* _parent)
{
	//Disabled for now
	return false;
}

/************************************************************************
Name: enemyAttack
Description : runs attack behaviour of enemy.
Parameters: cEnemy* _parent
Returns: None
Author : Jayden Burns
**************************************************************************/
void cAsteroidBehaviour::enemyAttack(cEnemy* _parent)
{
	return;
}

/************************************************************************
Name: enemyMove
Description : runs move behaviour of enemy.
Parameters: cEnemy* _parent
Returns: None
Author : Jayden Burns
**************************************************************************/
void cAsteroidBehaviour::enemyMove(cEnemy* _parent)
{
	sf::Vector2f NewPosition = _parent->getPosition() + _parent->getMovement();
	_parent->setPosition(NewPosition);
}

void cAsteroidBehaviour::setupEnemy(cEnemy* _parent, sf::Vector2f _position)
{
	_parent->setPosition(_position);
	_parent->setHealth(5);
	_parent->setState(Idle);
	_parent->setAwake(true);
	_parent->setBehaviour(this);
	_parent->setEnemyType(Type_Asteroid);
	_parent->setRotation(randRangeFloat(0, 180));
	pickDirection(_parent);
	_parent->setDamageStrength(1);
}

/************************************************************************
Name: pickDirection
Description : picks initial direction of asteroid
Parameters: cEnemy* _parent
Returns: None
Author : Jayden Burns
**************************************************************************/
void cAsteroidBehaviour::pickDirection(cEnemy* _parent)
{
	//TO DO - Set Speed by multiplying RandX or RandY
	float RandXDirection = randRangeFloat(-1, 1);
	float RandYDirection = randRangeFloat(-1, 1);
	_parent->setMovement(sf::Vector2f(RandXDirection, RandYDirection));
}

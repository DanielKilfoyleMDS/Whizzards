#include "cAsteroidBehaviour.h"
#include "cEnemy.h"


cAsteroidBehaviour::cAsteroidBehaviour()
{
}

cAsteroidBehaviour::~cAsteroidBehaviour()
{
}

bool cAsteroidBehaviour::TickEnemy(cEnemy* _parent)
{
	if (_parent != nullptr)
	{
		if (_parent->getAwake())
		{
			//Logic - Asteroid can only drift.
			switch (_parent->getState())
			{
			case Idle:
				Move(_parent);
				break;
			default:
				_parent->setState(Idle);
				break;
			}
		}
	}

	if (CheckDeath(_parent))
	{
		return false;
	}
	return true;

}

bool cAsteroidBehaviour::CheckDeath(cEnemy* _parent)
{
	if (_parent->getHealth() < 1)
	{
		return true;
	}
	return false;
}

bool cAsteroidBehaviour::CanAttack(cEnemy* _parent)
{
	//Disabled for now
	return false;
}

void cAsteroidBehaviour::Attack(cEnemy* _parent)
{
	return;
}

void cAsteroidBehaviour::Move(cEnemy* _parent)
{
	sf::Vector2f NewPosition = _parent->getPosition() + _parent->getMovement();
	_parent->SetPosition(NewPosition);

	//TODO - ScreenWrap
}


//TODO - Death function

//TODO - Variables for size
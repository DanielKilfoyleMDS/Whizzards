#include "cAsteroidBehaviour.h"
#include "cEnemy.h"


cAsteroidBehaviour::cAsteroidBehaviour()
{
}

cAsteroidBehaviour::~cAsteroidBehaviour()
{
}

void cAsteroidBehaviour::TickEnemy(cEnemy* _Parent)
{
	if (_Parent != nullptr)
	{
		if (_Parent->getAwake())
		{
			//Logic - Asteroid can only drift.
			switch (_Parent->getState())
			{
			case Idle:
				Move(_Parent);
				break;
			default:
				_Parent->setState(Idle);
				break;
			}
		}
	}
}

bool cAsteroidBehaviour::CanAttack(cEnemy* _Parent)
{
	//Disabled for now
	return false;
}

void cAsteroidBehaviour::Attack(cEnemy* _Parent)
{
	return;
}

void cAsteroidBehaviour::Move(cEnemy* _Parent)
{
	sf::Vector2f NewPosition = _Parent->getPosition() + _Parent->getMovement();
	_Parent->SetPosition(NewPosition);

	//HANDLE SCREEN WRAP!!
}


//TODO - Death function

//TODO - Variables for size
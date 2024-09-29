#include "cEnemyDrift.h"
#include "cEnemy.h"

//TODO - Set variables here
cEnemyDrift::cEnemyDrift()
{
}

cEnemyDrift::~cEnemyDrift()
{
}

void cEnemyDrift::TickEnemy(cEnemy* _Parent)
{
	if (_Parent != nullptr)
	{
		if (_Parent->IsAwake())
		{
			//Logic - Asteroid can only drift.
			switch (_Parent->GetState())
			{
			case Idle:
				Move(_Parent);
				break;
			default:
				_Parent->SetState(Idle);
				break;
			}
		}
	}
}

bool cEnemyDrift::CanAttack(cEnemy* _Parent)
{
	//Disabled for now
	return false;
}

void cEnemyDrift::Attack(cEnemy* _Parent)
{
	return;
}

void cEnemyDrift::Move(cEnemy* _Parent)
{
	sf::Vector2f NewPosition = _Parent->getPosition() + _Parent->GetDrift();
	_Parent->SetPosition(NewPosition);

	//HANDLE SCREEN WRAP!!
}


//TODO - Death function

//TODO - Variables for size
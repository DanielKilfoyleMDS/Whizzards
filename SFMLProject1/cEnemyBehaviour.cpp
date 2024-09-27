#include "cEnemyBehaviour.h"
#include "cEnemy.h"

cEnemyBehaviour::cEnemyBehaviour()
{
}

cEnemyBehaviour::~cEnemyBehaviour()
{
}

void cEnemyBehaviour::TickEnemy(cEnemy* _Parent)
{
	if (_Parent != nullptr)
	{
		if (_Parent->IsAwake())
		{
			//First do any logic checks we need to do

			//Then use switch statement to run next function
			switch (_Parent->GetState())
			{
			case Idle:
				break;
			case Wander:
				break;
			case Seek:
				break;
			default:
				break;
			}
		}
	}
}

bool cEnemyBehaviour::CanAttack(cEnemy* _Parent)
{
	return false;
}

void cEnemyBehaviour::Attack(cEnemy* _Parent)
{
}

void cEnemyBehaviour::Move(cEnemy* _Parent)
{
}

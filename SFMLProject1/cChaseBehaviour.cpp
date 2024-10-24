#include "cChaseBehaviour.h"
#include "cEnemy.h"
#include "MathLibrary.h"

cChaseBehaviour::cChaseBehaviour()
{
}

cChaseBehaviour::~cChaseBehaviour()
{
}

bool cChaseBehaviour::tickEnemy(cEnemy* _parent, float _deltaTime)
{
	//Attack(Chase) if available
	canAttack(_parent);
	enemyMove(_parent); //Otherwise move random style

	_parent->setFrame(_parent->getFrame() + _parent->framesPassed(_deltaTime));
	if (_parent->getFrame() > 2)
	{
		_parent->setFrame(0);
	}

	if (checkDeath(_parent))
	{
		return false;
	}
	return true;
}

bool cChaseBehaviour::checkDeath(cEnemy* _parent)
{
	if (_parent->getHealth() < 1)
	{
		return true;
	}
	return false;
}

bool cChaseBehaviour::canAttack(cEnemy* _parent)
{
	if(m_FirstPlayer == nullptr && m_SecondPlayer == nullptr) return false;

	float DistanceFirstPlayer = GetDistanceToPlayer(_parent,m_FirstPlayer);
	float DistanceSecondPlayer = GetDistanceToPlayer(_parent,m_SecondPlayer);
	if (DistanceFirstPlayer < DistanceSecondPlayer && DistanceFirstPlayer < maxChaseRange)
	{
		ChasePlayer(_parent, m_FirstPlayer);
		return true;
	}
	else if (DistanceSecondPlayer < DistanceFirstPlayer && DistanceSecondPlayer < maxChaseRange)
	{
		ChasePlayer(_parent, m_SecondPlayer);
		return true;
	}
	return false;
}

void cChaseBehaviour::enemyAttack(cEnemy* _parent)
{
}

void cChaseBehaviour::enemyMove(cEnemy* _parent)
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

void cChaseBehaviour::pickDirection(cEnemy* _parent)
{
	float RandXDirection = randRangeFloat(-1, 1);
	float RandYDirection = randRangeFloat(-1, 1);

	float Movetime = 5 * randRangeFloat(20, 40);
	_parent->setMoveTime(Movetime);
	_parent->setMovement(sf::Vector2f(RandXDirection, RandYDirection));
}

void cChaseBehaviour::setPlayers(cCharacter* _FirstPlayer)
{
	m_FirstPlayer = _FirstPlayer;
	m_SecondPlayer = nullptr;
}

void cChaseBehaviour::setPlayers(cCharacter* _FirstPlayer, cCharacter* _SecondPlayer)
{
	m_FirstPlayer = _FirstPlayer;
	m_SecondPlayer = _SecondPlayer;
}

float cChaseBehaviour::GetDistanceToPlayer(cEnemy* _parent, cCharacter* _Player)
{
	//returns value larger than chase range so we can't chase non-existent player
	if (_Player == nullptr) return maxChaseRange + 1; 
	else
	{
		sf::Vector2f Distance = _parent->getPosition() -_Player->getPosition();
		return VectorLength(Distance);
	}
}

void cChaseBehaviour::ChasePlayer(cEnemy* _parent, cCharacter* _player)
{
	//Move To function needed to be able to move towards a specific spot instead of moving towards set position

	sf::Vector2f Direction = _player->getPosition() - _parent->getPosition();
	Normalize(Direction);
	Direction = Normalize(Direction);
	_parent->setMovement(Direction);

}

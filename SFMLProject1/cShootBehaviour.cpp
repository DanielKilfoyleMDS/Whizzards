#include "cShootBehaviour.h"
#include "cEnemy.h"
#include "MathLibrary.h"

cShootBehaviour::cShootBehaviour()
{
}

cShootBehaviour::~cShootBehaviour()
{
}

bool cShootBehaviour::tickEnemy(cEnemy* _parent, float _deltaTime)
{
	enemyMove(_parent);
	canAttack(_parent);
	

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

bool cShootBehaviour::checkDeath(cEnemy* _parent)
{
	return false;
}

bool cShootBehaviour::canAttack(cEnemy* _parent)
{
	if (m_FirstPlayer == nullptr && m_SecondPlayer == nullptr) return false;

	float DistanceFirstPlayer = getDistanceToPlayer(_parent,m_FirstPlayer);
	float DistanceSecondPlayer = getDistanceToPlayer(_parent,m_SecondPlayer);
	if (DistanceFirstPlayer < DistanceSecondPlayer && DistanceFirstPlayer < AttackRange)
	{
		//Shoot at player
		shootPlayer(_parent, m_FirstPlayer);
		return true;
	}
	else if (DistanceSecondPlayer < DistanceFirstPlayer && DistanceSecondPlayer < AttackRange)
	{
		//Shoot at player
		shootPlayer(_parent, m_SecondPlayer);
		return true;
	}

	return false;
}

void cShootBehaviour::enemyAttack(cEnemy* _parent)
{
	//Shoot A Projectile.
	// Uh... Hmm.
}

void cShootBehaviour::enemyMove(cEnemy* _parent)
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

void cShootBehaviour::pickDirection(cEnemy* _parent)
{
	float RandXDirection = randRangeFloat(-1, 1);
	float RandYDirection = randRangeFloat(-1, 1);

	float Movetime = 5 * randRangeFloat(20, 40);
	_parent->setMoveTime(Movetime);
	_parent->setMovement(sf::Vector2f(RandXDirection, RandYDirection));
}

void cShootBehaviour::setupEnemy(cEnemy* _parent, sf::Vector2f _position)
{
	_parent->setPosition(_position);
	_parent->setHealth(10);
	_parent->setEnemyType(Type_Projectile);

	_parent->setState(Idle);
	_parent->setAwake(true);
	_parent->setBehaviour(this);
	_parent->setDamageStrength(2);
}

void cShootBehaviour::setPlayers(cCharacter* _FirstPlayer)
{
	m_FirstPlayer = _FirstPlayer;
	m_SecondPlayer = nullptr;
}

void cShootBehaviour::setPlayers(cCharacter* _FirstPlayer, cCharacter* _SecondPlayer)
{
	m_FirstPlayer = _FirstPlayer;
	m_SecondPlayer = _SecondPlayer;
}

float cShootBehaviour::getDistanceToPlayer(cEnemy* _parent, cCharacter* _player)
{
		//returns value larger than chase range so we can't chase non-existent player
	if (_player == nullptr) return AttackRange + 1;
	else
	{
		sf::Vector2f Distance = _parent->getPosition() - _player->getPosition();
		return VectorLength(Distance);
	}
}

void cShootBehaviour::shootPlayer(cEnemy* _parent, cCharacter* _target)
{
	std::cout << "SHOOT" << std::endl;
}

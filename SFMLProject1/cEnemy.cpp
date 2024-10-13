#include "cEnemy.h"


cEnemy::cEnemy(sf::Sprite* sprite, sf::Vector2f position)
	: cCharacter(sprite, position)
{
	//Runs original constructor and then additional logic below
	m_bAwake = false;
	m_Behaviour = nullptr;
	m_State = Idle;
}

cEnemy::~cEnemy()
{
}

void cEnemy::tick()
{
	if(m_Behaviour != nullptr && getAwake())
	{

		if (m_Behaviour->TickEnemy(this));
		{
			if (m_fMoveTime > 0)
			{
				m_fMoveTime--;
			}
		}
	}
	
	if (m_fcurrentHealth <= 0)
	{
		//UNLOAD
		m_bAwake = false;
	}
	
}

bool cEnemy::getAwake()
{
	return m_bAwake;
}

void cEnemy::setAwake(bool _bAwake)
{
	m_bAwake = _bAwake;
}

void cEnemy::ClearEnemy()
{
	m_Behaviour = nullptr;
	m_bAwake = false;
}

EnemyState cEnemy::getState()
{
	return m_State;
}

void cEnemy::setState(EnemyState _state)
{
	m_State = _state;
}

void cEnemy::setBehaviour(cEnemyBehaviour* _behaviour)
{
	m_Behaviour = _behaviour;
}

sf::Vector2f cEnemy::getMovement()
{
	return m_movement;
}

void cEnemy::setMovement(sf::Vector2f _movement)
{
	m_movement = _movement;
}

void cEnemy::setMoveTime(float _moveTime)
{
	m_fMoveTime = _moveTime;
}

float cEnemy::getMoveTime()
{
	return m_fMoveTime;
}

void cEnemy::OtherCollide(cCharacter* _Character)
{
	//THIS IS ALWAYS A PLAYER!!!
	if(m_bAwake != true) return;
	_Character->setHealth(_Character->getHealth() - m_fdamage);
}

void cEnemy::SetDamageStrength(float _Damage)
{
	m_fdamage = _Damage;
}

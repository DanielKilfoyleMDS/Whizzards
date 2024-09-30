#include "cEnemy.h"


cEnemy::cEnemy(std::string _filePath, std::string _characterName, sf::Vector2f _startPosition)
	: cCharacter(_filePath, _characterName, _startPosition)
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
		m_Behaviour->TickEnemy(this);
	}
	//EXPAND - Unspawn if failing
}

bool cEnemy::getAwake()
{
	return m_bAwake;
}

void cEnemy::setAwake(bool _bAwake)
{
	m_bAwake = _bAwake;
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

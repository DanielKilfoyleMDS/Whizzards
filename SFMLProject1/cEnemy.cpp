#include "cEnemy.h"


cEnemy::cEnemy(std::string _FilePath, std::string _CharacterName, sf::Vector2f _StartPosition)
	: cCharacter(_FilePath, _CharacterName, _StartPosition)
{
	//Runs original constructor and then additional logic below
	m_bAwake = false;
	m_Behaviour = nullptr;
	m_State = Idle;
}

cEnemy::~cEnemy()
{
}

void cEnemy::Tick()
{
	if (IsAwake())
	{
		m_Behaviour->TickEnemy(this);
	}
}

bool cEnemy::IsAwake()
{
	return m_bAwake;
}

void cEnemy::SetAwake(bool _Awake)
{
	m_bAwake = _Awake;
}

EnemyState cEnemy::GetState()
{
	return m_State;
}

void cEnemy::SetState(EnemyState _State)
{
}

void cEnemy::SetBehaviour(cEnemyBehaviour* _Behaviour)
{
	m_Behaviour = _Behaviour;
}

sf::Vector2f cEnemy::GetDrift()
{
	return m_Direction * m_Speed;
}

void cEnemy::SetDrift(sf::Vector2f _Dir, float Speed)
{
	m_Direction = _Dir;
	m_Speed = Speed;
}

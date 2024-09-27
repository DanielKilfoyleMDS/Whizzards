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
}

bool cEnemy::IsAwake()
{
	return m_bAwake;
}

void cEnemy::SetAwake(bool _Awake)
{
	m_bAwake = _Awake;
}

void cEnemy::SetState(EnemyState _State)
{
}

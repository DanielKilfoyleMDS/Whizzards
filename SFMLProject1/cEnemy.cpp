/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : cEnemy.cpp
Description : Base Enemy for Whizzards Game
Author : Jayden Burns
Mail : JaydenBurns@mds.ac.nz
**************************************************************************/
#include "cEnemy.h"
#include "cPlayer.h"

/************************************************************************
Name: cEnemy
Description : Enemy class Constructor for Whizzards Game
Parameters: sf::Sprite* _sprite, sf::Vector2f _startPosition)
Returns: None
Author : Jayden Burns
**************************************************************************/
cEnemy::cEnemy(sf::Sprite* _sprite, sf::Vector2f _startPosition)
	: cCharacter(_sprite, _startPosition)
{
	//Runs original constructor and then additional logic below
	m_bAwake = false;
	m_Behaviour = nullptr;
	m_enemyState = Idle;
	m_characterType = Enemy;
}

/************************************************************************
Name: ~cEnemy
Description : Enemy class Deconstructor
Parameters: None
Returns: None
Author : Jayden Burns
**************************************************************************/
cEnemy::~cEnemy()
{
	//Behaviour belongs to Pool Class, not Enemy
	m_Behaviour = nullptr;
}


/************************************************************************
Name: tick
Description : Tick Behaviour for Enemy Class.
Parameters: None
Returns: None
Author : Jayden Burns
**************************************************************************/
void cEnemy::tick(float _deltaTime)
{
	handleHurt(_deltaTime);

	if(m_Behaviour != nullptr && getAwake())
	{
		if (m_Behaviour->tickEnemy(this, _deltaTime));
		{
			if (m_fmoveTime > 0)
			{
				m_fmoveTime--;
			}
		}
	}

	if (m_fHurtTime > 0)
	{
		m_iCurrentFrame = -1;
	}
	
	if (m_fcurrentHealth <= 0)
	{
		m_bAwake = false; //Sets it to be asleep. Pool will unload it.
	}
	
}

/************************************************************************
Name: getAwake
Description : Checks if enemy is set to be asleep (inactive)
Parameters: None
Returns: bool m_bAwake
Author : Jayden Burns
**************************************************************************/
bool cEnemy::getAwake()
{
	return m_bAwake;
}

/************************************************************************
Name: setAwake
Description : Sets enemy to be awake (true) or asleep (false)
Parameters: bool _bAwake
Returns: None
Author : Jayden Burns
**************************************************************************/
void cEnemy::setAwake(bool _bAwake)
{
	m_bAwake = _bAwake;
}

/************************************************************************
Name: clearEnemy
Description : Clears all stats of enemy as part of unloading
Parameters: None
Returns: None
Author : Jayden Burns
**************************************************************************/
void cEnemy::clearEnemy()
{
	//TODO - Clear more Values here
	m_Behaviour = nullptr;
	m_bAwake = false;
}

/************************************************************************
Name: getState()
Description : gets current EnemyState of this Enemy
Parameters: None
Returns: EnemyState m_enemyState
Author : Jayden Burns
**************************************************************************/
EnemyState cEnemy::getState()
{
	return m_enemyState;
}

/************************************************************************
Name: setState()
Description : Sets current EnemyState of this Enemy
Parameters: EnemyState _state
Returns:
Author : Jayden Burns
**************************************************************************/
void cEnemy::setState(EnemyState _state)
{
	m_enemyState = _state;
}

/************************************************************************
Name: setBehaviour()
Description : Sets current Behaviour of this Enemy
Parameters: cEnemyBehaviour* _behaviour
Returns: None
Author : Jayden Burns
**************************************************************************/
void cEnemy::setBehaviour(cEnemyBehaviour* _behaviour)
{
	m_Behaviour = _behaviour;
}

/************************************************************************
Name: getMovement()
Description : Gets current movement vector of this Enemy
Parameters: None
Returns: sf::Vector2f m_movement
Author : Jayden Burns
**************************************************************************/
sf::Vector2f cEnemy::getMovement()
{
	return m_movement;
}

/************************************************************************
Name: setMovement()
Description : Sets current movement vector of this Enemy
Parameters: sf::Vector2f _movement
Returns: None
Author : Jayden Burns
**************************************************************************/
void cEnemy::setMovement(sf::Vector2f _movement)
{
	m_movement = _movement * m_fmovespeed;
}

/************************************************************************
Name: setMoveTime()
Description : Sets current movement time of this Enemy
Parameters: float _moveTime
Returns: None
Author : Jayden Burns
**************************************************************************/
void cEnemy::setMoveTime(float _moveTime)
{
	m_fmoveTime = _moveTime;
}

/************************************************************************
Name: getMoveTime()
Description : Gets current movement time of this Enemy
Parameters: None
Returns: float _mfmoveTime
Author : Jayden Burns
**************************************************************************/
float cEnemy::getMoveTime()
{
	return m_fmoveTime;
}


/************************************************************************
Name: otherCollide()
Description : Handles Collision with Another Character
Parameters: cCharacter* _Character
Returns: None
Author : Jayden Burns
**************************************************************************/
void cEnemy::otherCollide(cCharacter* _Character)
{
	//THIS IS ALWAYS A PLAYER!!!

	if(m_bAwake != true) return;
	_Character->applyDamage(m_fdamage);

	cPlayer* collidingPlayer = dynamic_cast<cPlayer*>(_Character);
	if(collidingPlayer->isMoving())	applyDamage(2);
}

/************************************************************************
Name: setDamageStrength()
Description : sets Damage strength of enemy
Parameters: float _Damage
Returns: None
Author : Jayden Burns
**************************************************************************/
void cEnemy::setDamageStrength(float _Damage)
{
	m_fdamage = _Damage;
}


void cEnemy::setEnemyType(EnemyType _enemyType)
{
	m_enemyType = _enemyType;
}

EnemyType cEnemy::getEnemyType()
{
	return m_enemyType;
}

void cEnemy::applyDamage(float _Damage)
{
	if (m_fHurtTime > 0) return;
	m_fcurrentHealth -= _Damage;
	m_fHurtTime = m_fHurtMaxTime;
}

bool cEnemy::canShoot(float _dt)
{
	if (m_fShootTime > 0)
	{
		m_fShootTime -= _dt;
		return false;
	}
	else
	{

		return true;
	}
	
}

void cEnemy::resetShootTime()
{
	m_fShootTime = m_fMaxShootTime;
}



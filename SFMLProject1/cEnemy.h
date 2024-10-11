/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : cEnemy.h
Description : Base Enemy for Whizzards Game
Author : Jayden Burns
Mail : JaydenBurns@mds.ac.nz
**************************************************************************/
#pragma once
#include "cCharacter.h"
#include "cEnemyBehaviour.h"

/************************************************************************
Name: EnemyState
Description : Struct that determines which behaviour multi-behaviour enemies use
Values: Idle, Wander, Seek
Author : Jayden Burns
**************************************************************************/
enum EnemyState
{
	Idle,
	Wander,
	Seek
};


class cEnemy : public cCharacter
{
public:
	cEnemy(sf::Sprite* _sprite, sf::Vector2f _startPosition);
	~cEnemy();

	void tick();

	bool getAwake();
	void setAwake(bool _bAwake);

	void clearEnemy();

	EnemyState getState();
	void setState(EnemyState _state);
	void setBehaviour(cEnemyBehaviour* _behaviour);

	sf::Vector2f getMovement();
	void setMovement(sf::Vector2f _movement);
	void setMoveTime(float _moveTime);
	float getMoveTime();

	void otherCollide(cCharacter* _Character);
	void setDamageStrength(float _Damage);

private:

	EnemyState m_enemyState;

	//EnemyState m_State;
	cEnemyBehaviour* m_Behaviour;

	bool m_bAwake;

	//Asteroid Behaviour
	sf::Vector2f m_movement = sf::Vector2f(0, 0);
	float m_fmoveTime = 0;

	//Damage values
	float m_fdamage = 0;


	//Follow Behaviour
	sf::Vector2f m_targetPosition = sf::Vector2f(0, 0);

};
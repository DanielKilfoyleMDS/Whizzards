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

/************************************************************************
Name: EnemyType
Description : Struct that determines which type of Enemy it is (Set by Behaviour)
Values: Type_Asteroid, Type_Random, Type_Chase, Type_Projectile
Author : Jayden Burns
**************************************************************************/
enum EnemyType
{
	Type_Asteroid,
	Type_Random,
	Type_Chase,
	Type_Projectile
};


class cEnemy : public cCharacter
{
public:
	cEnemy(sf::Sprite* sprite, sf::Vector2f position);
	~cEnemy();

	void tick(float _deltaTime);


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


	void setEnemyType(EnemyType _enemyType);
	EnemyType getEnemyType();

	void applyDamage(float _Damage);

	bool canShoot(float _dt);
	void resetShootTime();

private:

	EnemyState m_enemyState;
	EnemyType m_enemyType;

	std::vector<cEnemy*> m_ActiveEnemies;   // Active enemies
	std::vector<cEnemy*> m_InactiveEnemies; // Inactive enemies (not used)

	//EnemyState m_State;
	cEnemyBehaviour* m_Behaviour;

	bool m_bAwake;

	//Asteroid Behaviour
	sf::Vector2f m_movement = sf::Vector2f(0, 0);
	float m_fmoveTime = 0;
	float m_fmovespeed = 1;

	//Damage values
	float m_fdamage = 10.0f;


	//Follow Behaviour
	sf::Vector2f m_targetPosition = sf::Vector2f(0, 0);

	//Shoot Behaviour
	float m_fShootTime = 0;
	float m_fMaxShootTime = 2.5f;

};
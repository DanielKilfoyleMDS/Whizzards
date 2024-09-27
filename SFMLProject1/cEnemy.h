#pragma once
#include "cCharacter.h"
#include "cEnemyBehaviour.h"

enum EnemyState
{
	Idle,
	Wander,
	Seek
};


class cEnemy: public cCharacter
{
public:
	cEnemy(std::string _FilePath, std::string _CharacterName, sf::Vector2f _StartPosition);
	~cEnemy();

	//Handle Logic
	void Tick();

	bool IsAwake();
	void SetAwake(bool _Awake);

	//HandleLootPool
	void ClearEnemy();
	void SetupEnemy();

	EnemyState GetState();
	void SetState(EnemyState _State);

private:
	
	EnemyState m_State;

	//EnemyState m_State;
	cEnemyBehaviour* m_Behaviour;

	bool m_bAwake;
};

//Option A: Subclasses of Enemy
//Option B: references to behaviour classes - such as move style and attack styke
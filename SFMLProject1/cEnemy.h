#pragma once
#include "cCharacter.h"
#include "cEnemyBehaviour.h"

enum EnemyState
{
	Idle,
	Wander,
	Seek
};


class cEnemy : public cCharacter
{
public:
	cEnemy(std::string _FilePath, std::string _CharacterName, sf::Vector2f _StartPosition);
	~cEnemy();

	//Handle Logic
	void Tick();

	bool IsAwake();
	void SetAwake(bool _Awake);

	//HandleLootPool
	//void ClearEnemy();
	//void SetupEnemy();

	EnemyState GetState();
	void SetState(EnemyState _State);
	void SetBehaviour(cEnemyBehaviour* _Behaviour);

	//TODO - Calcluate not Get
	sf::Vector2f GetDrift();
	void SetDrift(sf::Vector2f _Dir, float Speed);

private:

	EnemyState m_State;

	//EnemyState m_State;
	cEnemyBehaviour* m_Behaviour;

	bool m_bAwake;

	//TODO Combine Direction/speed,
	//Asteroid Behaviour
	sf::Vector2f m_Direction = sf::Vector2f(0, 0);
	//TODO fix Variable types
	float m_Speed = 0.0f;

	//Follow Behaviour
	//TODO fix Variable types
	sf::Vector2f Target = sf::Vector2f(0, 0);

};
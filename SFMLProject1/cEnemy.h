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

	sf::Vector2f GetDrift();
	void SetDrift(sf::Vector2f _Dir, float Speed);

private:

	EnemyState m_State;

	//EnemyState m_State;
	cEnemyBehaviour* m_Behaviour;

	bool m_bAwake;

	//Asteroid Behaviour
	sf::Vector2f m_Direction = sf::Vector2f(0, 0);
	float m_Speed = 0.0f;

	//Follow Behaviour
	sf::Vector2f Target = sf::Vector2f(0, 0);

};
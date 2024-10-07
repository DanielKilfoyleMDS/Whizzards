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
	cEnemy(sf::Sprite* _sprite, sf::Vector2f _startPosition);
	~cEnemy();

	void tick();

	bool getAwake();
	void setAwake(bool _bAwake);

	void ClearEnemy();
	//void SetupEnemy();

	EnemyState getState();
	void setState(EnemyState _state);
	void setBehaviour(cEnemyBehaviour* _behaviour);

	sf::Vector2f getMovement();
	void setMovement(sf::Vector2f _movement);
	void setMoveTime(float _moveTime);
	float getMoveTime();

	void OtherCollide(cCharacter* _Character);
	void SetDamageStrength(float _Damage);

private:

	EnemyState m_State;

	//EnemyState m_State;
	cEnemyBehaviour* m_Behaviour;

	bool m_bAwake;

	//Asteroid Behaviour
	sf::Vector2f m_movement = sf::Vector2f(0, 0);
	float m_fMoveTime = 0;

	//Damage values
	float m_fdamage = 0;


	//Follow Behaviour
	sf::Vector2f m_targetPosition = sf::Vector2f(0, 0);

};
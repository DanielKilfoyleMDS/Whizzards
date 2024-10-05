#pragma once
#include "cEnemyBehaviour.h"
#include "SFML/Graphics.hpp"

class cAsteroidBehaviour : public cEnemyBehaviour
{
public:
	cAsteroidBehaviour();
	~cAsteroidBehaviour();

	bool TickEnemy(cEnemy* _parent) override;

	bool CheckDeath(cEnemy* _parent) override;

	bool CanAttack(cEnemy* _parent) override;
	void Attack(cEnemy* _parent) override;

	void Move(cEnemy* _parent) override;

};


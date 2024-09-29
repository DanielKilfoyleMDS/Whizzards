#pragma once
#include "cEnemyBehaviour.h"
//TODO - Rename Asteroid
//TODO - Keep variables in enemy
class cEnemyDrift: public cEnemyBehaviour
{
public:
	cEnemyDrift();
	~cEnemyDrift();

	void TickEnemy(cEnemy* _Parent) override;

	bool CanAttack(cEnemy* _Parent) override;
	void Attack(cEnemy* _Parent) override;

	void Move(cEnemy* _Parent) override;

};


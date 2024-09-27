#pragma once
#include "cEnemyBehaviour.h"

class cEnemyDrift: public cEnemyBehaviour
{
	cEnemyDrift();
	~cEnemyDrift();

	void TickEnemy(cEnemy* _Parent) override;

	bool CanAttack(cEnemy* _Parent) override;
	void Attack(cEnemy* _Parent) override;

	void Move(cEnemy* _Parent) override;

};


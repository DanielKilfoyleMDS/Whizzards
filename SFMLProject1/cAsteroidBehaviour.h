#pragma once
#include "cEnemyBehaviour.h"
//TODO - Rename Asteroid

class cAsteroidBehaviour : public cEnemyBehaviour
{
public:
	cAsteroidBehaviour();
	~cAsteroidBehaviour();

	void TickEnemy(cEnemy* _Parent) override;

	bool CanAttack(cEnemy* _Parent) override;
	void Attack(cEnemy* _Parent) override;

	void Move(cEnemy* _Parent) override;

};


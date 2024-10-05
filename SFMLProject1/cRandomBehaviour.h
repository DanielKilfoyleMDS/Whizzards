#pragma once
#include "cEnemyBehaviour.h"

class cRandomBehaviour : public cEnemyBehaviour
{
public:
	cRandomBehaviour();
	~cRandomBehaviour();

	bool TickEnemy(cEnemy* _parent) override;

	bool CheckDeath(cEnemy* _parent) override;

	bool CanAttack(cEnemy* _parent) override;
	void Attack(cEnemy* _parent) override;

	void Move(cEnemy* _parent) override;

	void PickDirection(cEnemy* _parent);
};
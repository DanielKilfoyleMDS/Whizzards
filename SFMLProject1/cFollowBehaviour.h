#pragma once
#include "cEnemyBehaviour.h"
class cFollowBehaviour : public cEnemyBehaviour
{
	cFollowBehaviour();
	~cFollowBehaviour();


	//Handles Logic
	bool TickEnemy(class cEnemy* _parent) override;

	bool CheckDeath(cEnemy* _parent) override;

	//Checks if Enemy can Attack
	bool CanAttack(class cEnemy* _parent) override;
	void Attack(class cEnemy* _parent) override;

	//Moves Enemy
	void Move(class cEnemy* _parent) override;
};


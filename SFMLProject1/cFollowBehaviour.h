#pragma once
#include "cEnemyBehaviour.h"
class cFollowBehaviour : public cEnemyBehaviour
{
	cFollowBehaviour();
	~cFollowBehaviour();


	//Handles Logic
	bool tickEnemy(class cEnemy* _parent) override;

	bool checkDeath(cEnemy* _parent) override;

	//Checks if Enemy can Attack
	bool canAttack(class cEnemy* _parent) override;
	void enemyAttack(class cEnemy* _parent) override;

	//Moves Enemy
	void enemyMove(class cEnemy* _parent) override;
};


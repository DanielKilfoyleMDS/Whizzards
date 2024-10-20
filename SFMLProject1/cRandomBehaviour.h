/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : cRandomBehaviour.h
Description : Behaviour class for Random wander enemy
Author : Jayden Burns
Mail : JaydenBurns@mds.ac.nz
**************************************************************************/
#pragma once
#include "cEnemyBehaviour.h"

class cRandomBehaviour : public cEnemyBehaviour
{
public:
	cRandomBehaviour();
	~cRandomBehaviour();

	bool tickEnemy(cEnemy* _parent, float _deltaTime) override;

	bool checkDeath(cEnemy* _parent) override;

	bool canAttack(cEnemy* _parent) override;
	void enemyAttack(cEnemy* _parent) override;

	void enemyMove(cEnemy* _parent) override;

	void pickDirection(cEnemy* _parent);
};
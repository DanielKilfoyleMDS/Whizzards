/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : cShootBehaviour.h
Description : Behaviour class for Projectile Shooting enemy
Author : Jayden Burns
Mail : JaydenBurns@mds.ac.nz
**************************************************************************/
#pragma once
#include "cEnemyBehaviour.h"
class cShootBehaviour : public cEnemyBehaviour
{
public:
	cShootBehaviour();
	~cShootBehaviour();

	bool tickEnemy(cEnemy* _parent, float _deltaTime) override;

	bool checkDeath(cEnemy* _parent) override;

	bool canAttack(cEnemy* _parent) override;
	void enemyAttack(cEnemy* _parent) override;

	void enemyMove(cEnemy* _parent) override;
};


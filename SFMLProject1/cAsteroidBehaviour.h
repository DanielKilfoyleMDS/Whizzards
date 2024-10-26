/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : cAsteroidBehaviour.h
Description : Behaviour class for Asteroid enemy
Author : Jayden Burns
Mail : JaydenBurns@mds.ac.nz
**************************************************************************/
#pragma once
#include "cEnemyBehaviour.h"
#include "SFML/Graphics.hpp"

class cAsteroidBehaviour : public cEnemyBehaviour
{
public:
	cAsteroidBehaviour();
	~cAsteroidBehaviour();

	bool tickEnemy(cEnemy* _parent, float _deltaTime) override;

	bool checkDeath(cEnemy* _parent) override;

	bool canAttack(cEnemy* _parent) override;
	void enemyAttack(cEnemy* _parent) override;

	void enemyMove(cEnemy* _parent) override;

	void setupEnemy(cEnemy* _parent, sf::Vector2f _position) override;

	void pickDirection(cEnemy* _parent);

	//TODO - Asteroid Split logic, Size variables

};


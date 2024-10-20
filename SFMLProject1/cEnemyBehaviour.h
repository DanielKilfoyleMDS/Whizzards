/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : cEnemyBehaviour.h
Description : Base Enemybehaviour Class, overwritten by subclasses
Author : Jayden Burns
Mail : JaydenBurns@mds.ac.nz
**************************************************************************/
#pragma once
#include "SFML/Graphics.hpp"

class cEnemyBehaviour
{
public: 
	cEnemyBehaviour();
	~cEnemyBehaviour();
	

	/************************************************************************
	Name: tickEnemy
	Description : runs behaviour on enemy. Overwritten by Subclasses
	Parameters: cEnemy* _parent
	Returns: bool - false if unsuccessful.
	Author : Jayden Burns
	**************************************************************************/
	virtual bool tickEnemy(class cEnemy* _parent) = 0;

	/************************************************************************
	Name: checkDeath
	Description : checks if enemy should be dead. Overwritten by Subclasses
	Parameters: cEnemy* _parent
	Returns: bool - true if it should be dead
	Author : Jayden Burns
	**************************************************************************/
	virtual bool checkDeath(cEnemy* _parent) = 0;

	/************************************************************************
	Name: canAttack
	Description : checks if enemy canAttack. Overwritten by Subclasses
	Parameters: cEnemy* _parent
	Returns: bool - true if can Attack
	Author : Jayden Burns
	**************************************************************************/
	virtual bool canAttack(class cEnemy* _parent) = 0;

	/************************************************************************
	Name: enemyAttack
	Description : runs attack behaviour of enemy. Overwritten by Subclasses
	Parameters: cEnemy* _parent
	Returns: None
	Author : Jayden Burns
	**************************************************************************/
	virtual void enemyAttack(class cEnemy* _parent) = 0;

	/************************************************************************
	Name: enemyMove
	Description : runs move behaviour of enemy. Overwritten by Subclasses
	Parameters: cEnemy* _parent
	Returns: None
	Author : Jayden Burns
	**************************************************************************/
	virtual void enemyMove(class cEnemy* _parent) = 0;


	void setBehaviourSprite(sf::Sprite* _reference);


protected:
	sf::Sprite* m_behaviourSprite = nullptr;

};


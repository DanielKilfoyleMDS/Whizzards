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
	void setupEnemy(cEnemy* _parent, sf::Vector2f _position) override;

	//Sets either first player or both players when run
	void setPlayers(class cCharacter* _FirstPlayer);
	void setPlayers(class cCharacter* _FirstPlayer, class cCharacter* _SecondPlayer);

	float getDistanceToPlayer(cEnemy* _parent, class cCharacter* _player);

	void shootPlayer(cEnemy* _parent, class cCharacter* _target);
	void pickDirection(cEnemy* _parent);

	void setProjectiles(sf::Sprite* _projSprite, std::vector<class cProjectile*>* _projList);

private:
	//Player Tracking - tracks nearest of these two To Shoot
	class cCharacter* m_FirstPlayer = nullptr;
	class cCharacter* m_SecondPlayer = nullptr;

	float m_fmovespeed = 2;
	float m_fAttackRange = 300.0f;
	float m_fDetectRange = 600.0f;

	//Projectile Stuff
	sf::Sprite* m_projSprite;
	std::vector<cProjectile*>* m_projList;
};


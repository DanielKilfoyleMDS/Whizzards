/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : cEnemyPool.h
Description : Enemy Pool for Whizzards Game
Author : Jayden Burns
Mail : JaydenBurns@mds.ac.nz
**************************************************************************/
#pragma once
#include "cEnemy.h"
#include "cAsteroidBehaviour.h"
#include "cRandomBehaviour.h"
class cEnemyPool
{
public:
	cEnemyPool(int _enemyCount, sf::Sprite* _defaultSprite, std::vector<cCharacter*>* _collisionVector);
	~cEnemyPool();

	bool loadAsteroidEnemy(sf::Vector2f _position, sf::Vector2f _movement, float _speed);
	bool loadRandomEnemy(sf::Vector2f _position);

	void tickEnemies();

	std::vector<cEnemy*> getActiveEnemies();
	std::vector<cEnemy*> getInactiveEnemies();

	void setBehaviourSprites(sf::Sprite* m_AsteroidSprite, sf::Sprite* m_RandomSprite);


private:
	std::vector<cEnemy*> m_enemiesInactive;
	std::vector<cEnemy*> m_enemiesActive;

	cAsteroidBehaviour m_AsteroidBehaviour;
	cRandomBehaviour m_RandomBehaviour;

	sf::Sprite* m_AsteroidSprite = nullptr;
	sf::Sprite* m_DefaultSprite = nullptr;
};


/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : cGameManager.h
Description : Game Manager class. Used for loading sprites once at runtime and for storing our collision vectors to be accessed by other classes
Author : Daniel Kilfoyle & Jayden Burns
Mail : DanielKilfoyle@mds.ac.nz & JaydenBurns@mds.ac.nz
**************************************************************************/

#pragma once
#include "SFML/Graphics.hpp"
#include "cCharacter.h"
#include "cProjectile.h"

class cGameManager
{
public:
	cGameManager();

	sf::Sprite* getEnemyAsteroidSprite();
	sf::Sprite* getEnemyRandomSprite();
	sf::Sprite* getEnemyDefaultSprite();
	sf::Sprite* getEnemyChaseSprite();


	sf::Sprite* getFirstPlayerSprite();
	sf::Sprite* getSecondPlayerSprite();
	sf::Sprite* getFirstPlayerProjectile();
	sf::Sprite* getSecondPlayerProjectile();




	void AddToCollisionList(cCharacter* _Character);
	cCharacter* GetFromCollisionList(int _ListPosition);
	std::vector<cCharacter*>* getCollisionList();
	std::vector<cProjectile*>* getProjectilesList();

private:
	//Collision
	std::vector<cCharacter*>* m_CollisionList;

	std::vector<cProjectile*>* m_ProjectileList;


	//Enemy Textures
	sf::Texture m_defaultEnemyTexture;
	sf::Texture m_asteroidTexture;
	sf::Texture m_randomEnemyTexture;
	sf::Texture m_chaseEnemyTexture;

	// Enemy Sprites
	sf::Sprite m_asteroidEnemySprite;
	sf::Sprite m_defaultEnemySprite;
	sf::Sprite m_randomEnemySprite;
	sf::Sprite m_chaseEnemySprite;

	// Player Sprites
	sf::Sprite m_firstPlayerSprite;
	sf::Sprite m_secondPlayerSprite;
	sf::Sprite m_blueProjectileSprite;
	sf::Sprite m_redProjectileSprite;

	// Player Textures
	sf::Texture m_firstPlayerTexture;
	sf::Texture m_secondPlayerTexture;
	sf::Texture m_blueProjectileTexture;
	sf::Texture m_redProjectileTexture;
};


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

	void LoadSprite(sf::Sprite* _Sprite, sf::Texture* _Texture, const std::string& _FilePath);

	sf::Sprite* getEnemyAsteroidSprite();
	sf::Sprite* getEnemyRandomSprite();
	sf::Sprite* getEnemyDefaultSprite();
	sf::Sprite* getEnemyChaseSprite();
	sf::Sprite* getEnemyTestSprite(int _Frame);


	sf::Sprite* getFirstPlayerSprite(int _frame);
	sf::Sprite* getSecondPlayerSprite(int _frame);

	sf::Sprite* getFirstPlayerProjectile(int _frame);
	sf::Sprite* getSecondPlayerProjectile(int _frame);

	sf::Sprite* getWandPickupSprite(int _frame);


	void AddToCollisionList(cCharacter* _Character);
	cCharacter* GetFromCollisionList(int _ListPosition);
	std::vector<cCharacter*>* getCollisionList();
	std::vector<cProjectile*>* getProjectilesList();

	void SetupEnemySprites();

private:
	//Collision
	std::vector<cCharacter*>* m_CollisionList;

	std::vector<cProjectile*>* m_ProjectileList;


	//Enemy Textures
	sf::Texture m_defaultEnemyTexture;
	sf::Texture m_asteroidTexture;
	sf::Texture m_randomEnemyTexture;
	sf::Texture m_chaseEnemyTexture;
	sf::Texture m_testEnemy1Texture;
	sf::Texture m_testEnemy2Texture;
	sf::Texture m_testEnemy3Texture;
	sf::Texture m_testEnemy4Texture;

	// Enemy Sprites
	sf::Sprite m_asteroidEnemySprite;
	sf::Sprite m_defaultEnemySprite;
	sf::Sprite m_randomEnemySprite;
	sf::Sprite m_chaseEnemySprite;
	sf::Sprite m_TestSprite1;
	sf::Sprite m_TestSprite2;
	sf::Sprite m_TestSprite3;
	sf::Sprite m_TestSprite4;

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

	//WandPickupSprites
	sf::Sprite m_wandPickupSprite;
	//WandPickup Textures
	sf::Texture m_wandPickupTexture;
};


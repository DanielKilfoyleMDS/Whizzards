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
	sf::Sprite* getEnemyChaseSprite(int _Frame);
	sf::Sprite* getEnemyTestSprite(int _Frame);


	sf::Sprite* getFirstPlayerSprite(int _frame);
	sf::Sprite* getSecondPlayerSprite(int _frame);
	sf::Sprite* getPlayerInvincSprite();

	sf::Sprite* getFirstPlayerProjectile(int _frame);
	sf::Sprite* getSecondPlayerProjectile(int _frame);
	sf::Sprite* getFireProjectile(int _frame);

	sf::Sprite* getWandPickupSprite(int _frame);


	void AddToCollisionList(cCharacter* _Character);
	cCharacter* GetFromCollisionList(int _ListPosition);
	std::vector<cCharacter*>* getCollisionList();
	std::vector<cProjectile*>* getProjectilesList();

	void SetupEnemySprites();
	void SetupProjectileSprites();
	void SetupPlayerSprites();

private:
	//Collision
	std::vector<cCharacter*>* m_CollisionList;

	std::vector<cProjectile*>* m_ProjectileList;


	//Enemy Textures
	sf::Texture m_defaultEnemyTexture;
	sf::Texture m_asteroidTexture;
	sf::Texture m_randomEnemyTexture1;
	sf::Texture m_randomEnemyTexture2;
	sf::Texture m_randomEnemyTexture3;
	sf::Texture m_chaseEnemyTexture1;
	sf::Texture m_chaseEnemyTexture2;
	sf::Texture m_chaseEnemyTexture3;

	// Enemy Sprites
	sf::Sprite m_asteroidEnemySprite;
	sf::Sprite m_defaultEnemySprite;
	sf::Sprite m_randomEnemySprite1;
	sf::Sprite m_randomEnemySprite2;
	sf::Sprite m_randomEnemySprite3;
	sf::Sprite m_chaseEnemySprite1;
	sf::Sprite m_chaseEnemySprite2;
	sf::Sprite m_chaseEnemySprite3;

	//Projectile Textures
	sf::Texture m_FireProjTex1;
	sf::Texture m_FireProjTex2;
	sf::Texture m_FireProjTex3;
	sf::Texture m_FireProjTex4;
	sf::Texture m_FireProjTex5;

	//Projectile Sprites
	sf::Sprite m_FireProjSprite1;
	sf::Sprite m_FireProjSprite2;
	sf::Sprite m_FireProjSprite3;
	sf::Sprite m_FireProjSprite4;
	sf::Sprite m_FireProjSprite5;

	// Player Sprites
	sf::Sprite m_firstPlayerForwardSprite;
	sf::Sprite m_firstPlayerRightSprite;
	sf::Sprite m_firstPlayerLeftSprite;
	sf::Sprite m_secondPlayerForwardSprite;
	sf::Sprite m_secondPlayerRightSprite;
	sf::Sprite m_secondPlayerLeftSprite;
	sf::Sprite m_playerInvincibleSprite;
	sf::Sprite m_blueProjectileSprite;
	sf::Sprite m_redProjectileSprite;

	// Player Textures
	sf::Texture m_firstPlayerForwardTexture;
	sf::Texture m_firstPlayerRightTexture;
	sf::Texture m_firstPlayerLeftTexture;
	sf::Texture m_secondPlayerForwardTexture;
	sf::Texture m_secondPlayerRightTexture;
	sf::Texture m_secondPlayerLeftTexture;
	sf::Texture m_playerInvincibleTexture;
	sf::Texture m_blueProjectileTexture;
	sf::Texture m_redProjectileTexture;

	//WandPickupSprites
	sf::Sprite m_wandPickupSprite;
	//WandPickup Textures
	sf::Texture m_wandPickupTexture;
};


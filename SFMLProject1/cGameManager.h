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
#include "SFML/Audio.hpp"
#include "cCharacter.h"
#include "cProjectile.h"

class cGameManager
{
public:
	cGameManager();

	void LoadSprite(sf::Sprite* _Sprite, sf::Texture* _Texture, const std::string& _FilePath);

	sf::Sprite* getEnemyAsteroidSprite(int _Frame);
	sf::Sprite* getEnemyRandomSprite(int _Frame);
	sf::Sprite* getEnemyDefaultSprite();
	sf::Sprite* getEnemyChaseSprite(int _Frame);
	sf::Sprite* getEnemyShootSprite(int _Frame);


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

	void LoadSound(sf::Sound* _Sound, sf::SoundBuffer* _Buffer, const std::string& _FilePath);
	void SetUpSounds();

	sf::Sound getProjectileFireSound();
	sf::Sound* getProjectileHitSound();
	
	sf::Sound* getPlayerDamageSound();
	sf::Sound getPlayerDeathSound();

	sf::Sound getPlayerIdleSound();

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
	sf::Texture m_shootEnemyTexture;
	sf::Texture m_shootEnemyTexture2;

	sf::Texture m_chaseEnemyTextureHurt;
	sf::Texture m_randomEnemyTextureHurt;
	sf::Texture m_asteroidTextureHurt;
	sf::Texture m_shootEnemyTextureHurt;


	// Enemy Sprites
	sf::Sprite m_asteroidEnemySprite;
	sf::Sprite m_asteroidEnemySpriteHurt;

	sf::Sprite m_defaultEnemySprite;
	sf::Sprite m_randomEnemySprite1;
	sf::Sprite m_randomEnemySprite2;
	sf::Sprite m_randomEnemySprite3;
	sf::Sprite m_chaseEnemySprite1;
	sf::Sprite m_chaseEnemySprite2;
	sf::Sprite m_chaseEnemySprite3;
	sf::Sprite m_chaseEnemySpriteHurt;
	sf::Sprite m_randomEnemySpriteHurt;

	sf::Sprite m_shootEnemySprite;
	sf::Sprite m_shootEnemySprite2;
	sf::Sprite m_shootEnemySpriteHurt;

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


	// Player Sounds
	sf::SoundBuffer m_PlayerDamageBuffer;
	sf::Sound m_PlayerDamageSound;

	sf::SoundBuffer m_PlayerDeathBuffer;
	sf::Sound m_PlayerDeathSound;

	sf::SoundBuffer m_MotorcycleMoveBuffer;
	sf::Sound m_MotorcycleMoveSound;

	sf::SoundBuffer m_MotorcycleIdleBuffer;
	sf::Sound m_MotorcycleIdleSound;

	// Enemy Sounds
	sf::SoundBuffer m_EnemyDamageBuffer;
	sf::Sound m_EnemyDamageSound;

	sf::SoundBuffer m_EnemyDeathBuffer;
	sf::Sound m_EnemyDeathSound;

	// Shared Sounds
	sf::SoundBuffer m_FireProjBuffer;
	sf::Sound m_FireProjSound;

	sf::SoundBuffer m_HitProjBuffer;
	sf::Sound m_HitProjSound;



};


#pragma once
#include "SFML/Graphics.hpp"
#include "cCharacter.h"

class cGameManager
{
public:
	cGameManager();

	sf::Sprite getAsteroidSprite();
	sf::Sprite getEnemyDefaultSprite();


	sf::Sprite getFirstPlayerSprite();
	sf::Sprite getSecondPlayerSprite();
	sf::Sprite getFirstPlayerProjectile();
	sf::Sprite getSecondPlayerProjectile();




	// Player Sprites
	sf::Sprite m_firstPlayerSprite;
	sf::Sprite m_secondPlayerSprite;

	// Enemy Sprites
	sf::Sprite m_asteroidEnemySprite;
	sf::Sprite m_defaultEnemySprite;

	sf::Sprite m_blueProjectileSprite;
	sf::Sprite m_redProjectileSprite;

	//Textures
	sf::Texture m_DefaultEnemyTexture;
	sf::Texture m_AsteroidTexture;

	sf::Texture m_firstPlayerTexture;
	sf::Texture m_secondPlayerTexture;

	sf::Texture m_blueProjectileTexture;
	sf::Texture m_redProjectileTexture;

	void AddToCollisionList(cCharacter* _Character);
	cCharacter* GetFromCollisionList(int _ListPosition);
	std::vector<cCharacter*>* GetCollisionList();

private:
	//Collision
	std::vector<cCharacter*>* m_CollisionList;
};


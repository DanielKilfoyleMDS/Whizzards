#pragma once
#include "SFML/Graphics.hpp"

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
};


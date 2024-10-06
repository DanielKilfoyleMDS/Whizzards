#pragma once
#include "SFML/Graphics.hpp"

class cGameManager
{
public:
	cGameManager();

private:
	// Player Sprites
	sf::Sprite* m_firstPlayerSprite;
	sf::Sprite* m_secondPlayerSprite;

	// Enemy Sprites
	sf::Sprite* m_asteroidEnemySprite;
	//sf::Sprite* 
};


#include "cGameManager.h"

cGameManager::cGameManager()
{
	// Loading all relevant sprites


	// Enemy Sprites
	sf::Texture m_AsteroidTexture;
	m_AsteroidTexture.loadFromFile("Resources/Textures/Sprites/EnemyDefault.png");
	m_asteroidEnemySprite.setTexture(m_AsteroidTexture);

	sf::Texture m_DefaultEnemyTexture;
	m_DefaultEnemyTexture.loadFromFile("Resources/Textures/Sprites/EnemyDefault.png");
	m_defaultEnemySprite.setTexture(m_DefaultEnemyTexture);


	// Player Sprites
	sf::Texture m_firstPlayerTexture;
	m_firstPlayerTexture.loadFromFile("Resources/Textures/Sprites/Blue Player.png");
	m_firstPlayerSprite.setTexture(m_firstPlayerTexture);

	sf::Texture m_secondPlayerTexture;
	m_secondPlayerTexture.loadFromFile("Resources/Textures/Sprites/Blue Player.png");
	m_secondPlayerSprite.setTexture(m_secondPlayerTexture);

	sf::Texture m_blueProjectileTexture;
	m_blueProjectileTexture.loadFromFile("Resources/Textures/Sprites/Projectile Blue.png");
	m_blueProjectileSprite.setTexture(m_blueProjectileTexture);

	sf::Texture m_redProjectileTexture;
	m_redProjectileTexture.loadFromFile("Resources/Textures/Sprites/Projectile Blue.png");
	m_redProjectileSprite.setTexture(m_redProjectileTexture);


}

sf::Sprite cGameManager::getAsteroidSprite()
{
	return m_asteroidEnemySprite;
}

#include "cGameManager.h"

cGameManager::cGameManager()
{
	//Prepare List
	m_CollisionList = new std::vector<cCharacter*>;
	m_ProjectileList = new std::vector<cProjectile*>;

	// Loading all relevant sprites


	// Enemy Sprites
	m_asteroidTexture.loadFromFile("Resources/Textures/Sprites/EnemyAsteroid.png");
	m_asteroidEnemySprite.setTexture(m_asteroidTexture);

	m_randomEnemyTexture.loadFromFile("Resources/Textures/Sprites/EnemyRandom.png");
	m_randomEnemySprite.setTexture(m_randomEnemyTexture);

	m_chaseEnemyTexture.loadFromFile("Resources/Textures/Sprites/EnemyChase.png");
	m_chaseEnemySprite.setTexture(m_chaseEnemyTexture);

	m_defaultEnemyTexture.loadFromFile("Resources/Textures/Sprites/EnemyDefault.png");
	m_defaultEnemySprite.setTexture(m_defaultEnemyTexture);


	// Player Sprites
	m_firstPlayerTexture.loadFromFile("Resources/Textures/Sprites/Blue Player.png");
	m_firstPlayerSprite.setTexture(m_firstPlayerTexture);

	m_secondPlayerTexture.loadFromFile("Resources/Textures/Sprites/Red Player.png");
	m_secondPlayerSprite.setTexture(m_secondPlayerTexture);

	m_blueProjectileTexture.loadFromFile("Resources/Textures/Sprites/Projectile Blue.png");
	m_blueProjectileSprite.setTexture(m_blueProjectileTexture);

	m_redProjectileTexture.loadFromFile("Resources/Textures/Sprites/Projectile Red.png");
	m_redProjectileSprite.setTexture(m_redProjectileTexture);


}

sf::Sprite* cGameManager::getEnemyAsteroidSprite()
{
	return &m_asteroidEnemySprite;
}

sf::Sprite* cGameManager::getEnemyRandomSprite()
{
	return &m_randomEnemySprite;
}

sf::Sprite* cGameManager::getEnemyDefaultSprite()
{
	return &m_defaultEnemySprite;
}

sf::Sprite* cGameManager::getEnemyChaseSprite()
{
	return  &m_chaseEnemySprite;
}

sf::Sprite* cGameManager::getFirstPlayerSprite()
{
	return &m_firstPlayerSprite;
}

sf::Sprite* cGameManager::getSecondPlayerSprite()
{
	return &m_secondPlayerSprite;
}

sf::Sprite* cGameManager::getFirstPlayerProjectile()
{
	return &m_blueProjectileSprite;
}

sf::Sprite* cGameManager::getSecondPlayerProjectile()
{
	return &m_redProjectileSprite;
}

void cGameManager::AddToCollisionList(cCharacter* _Character)
{
	m_CollisionList->push_back(_Character);
}

cCharacter* cGameManager::GetFromCollisionList(int _ListPosition)
{
	return m_CollisionList->at(_ListPosition);
}

std::vector<cCharacter*>* cGameManager::getCollisionList()
{
	return m_CollisionList;
}

std::vector<cProjectile*>* cGameManager::getProjectilesList()
{
	return m_ProjectileList;
}

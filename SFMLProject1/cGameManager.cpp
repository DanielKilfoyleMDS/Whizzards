#include "cGameManager.h"

/*************************************************************************
Name: cGameManager
Description : Constructs the game manager
Parameters: None
Returns: None
Author : Daniel Kilfoyle
**************************************************************************/
cGameManager::cGameManager()
{
	//Prepare List
	m_CollisionList = new std::vector<cCharacter*>;
	m_ProjectileList = new std::vector<cProjectile*>;

	// Loading all relevant sprites

	SetupEnemySprites();


	// Player Sprites
	m_firstPlayerTexture.loadFromFile("Resources/Textures/Sprites/Blue Player.png");
	m_firstPlayerSprite.setTexture(m_firstPlayerTexture);

	m_secondPlayerTexture.loadFromFile("Resources/Textures/Sprites/Red Player.png");
	m_secondPlayerSprite.setTexture(m_secondPlayerTexture);

	m_blueProjectileTexture.loadFromFile("Resources/Textures/Sprites/Projectile Blue.png");
	m_blueProjectileSprite.setTexture(m_blueProjectileTexture);

	m_redProjectileTexture.loadFromFile("Resources/Textures/Sprites/Projectile Red.png");
	m_redProjectileSprite.setTexture(m_redProjectileTexture);

	//Wand texture/sprite
	m_wandPickupTexture.loadFromFile("Resources/Textures/Sprites/wandpickup.png");
	m_wandPickupSprite.setTexture(m_wandPickupTexture);
}

/*************************************************************************
Name: getEnemyAsteroidSprite
Description : gets the sprite for the asteroid enemy type
Parameters: None
Returns: sf::Sprite pointer
Author : Daniel Kilfoyle
**************************************************************************/

sf::Sprite* cGameManager::getEnemyAsteroidSprite()
{
	return &m_asteroidEnemySprite;
}

/*************************************************************************
Name: getEnemyRandomSprite
Description : gets the sprite for the random enemy type
Parameters: None
Returns: sf::Sprite pointer
Author : Daniel Kilfoyle
**************************************************************************/
sf::Sprite* cGameManager::getEnemyRandomSprite()
{
	return &m_randomEnemySprite;
}

/*************************************************************************
Name: getEnemyDefaultSprite
Description : gets the sprite for the default enemy type
Parameters: None
Returns: sf::Sprite pointer
Author : Daniel Kilfoyle
**************************************************************************/
sf::Sprite* cGameManager::getEnemyDefaultSprite()
{
	return &m_defaultEnemySprite;
}

/*************************************************************************
Name: getEnemyChaseSprite
Description : gets the sprite for the chase enemy type
Parameters: None
Returns: sf::Sprite pointer
Author : Daniel Kilfoyle
**************************************************************************/
sf::Sprite* cGameManager::getEnemyChaseSprite()
{
	return  &m_chaseEnemySprite;
}

sf::Sprite* cGameManager::getEnemyTestSprite(int _Frame)
{
	if (_Frame == 0)
	{
		return &m_TestSprite1;
	}else if (_Frame == 1)
	{
		return &m_TestSprite2;
	}else if (_Frame == 2)
	{
		return &m_TestSprite3;
	}else if (_Frame == 3)
	{
		return &m_TestSprite4;
	}

	return nullptr;
}

/*************************************************************************
Name: getFirstPlayerSprite
Description : gets the sprite for the first player
Parameters: None
Returns: sf::Sprite pointer
Author : Daniel Kilfoyle
**************************************************************************/
sf::Sprite* cGameManager::getFirstPlayerSprite()
{
	return &m_firstPlayerSprite;
}

/*************************************************************************
Name: getSecondPlayerSprite
Description : gets the sprite for the second player
Parameters: None
Returns: sf::Sprite pointer
Author : Daniel Kilfoyle
**************************************************************************/
sf::Sprite* cGameManager::getSecondPlayerSprite()
{
	return &m_secondPlayerSprite;
}

/*************************************************************************
Name: getFirstPlayerProjectile
Description : gets the sprite for the first player's projectiles
Parameters: None
Returns: sf::Sprite pointer
Author : Daniel Kilfoyle
**************************************************************************/
sf::Sprite* cGameManager::getFirstPlayerProjectile()
{
	return &m_blueProjectileSprite;
}

/*************************************************************************
Name: getSecondPlayerProjectile
Description : gets the sprite for the second player's projectiles
Parameters: None
Returns: sf::Sprite pointer
Author : Daniel Kilfoyle
**************************************************************************/
sf::Sprite* cGameManager::getSecondPlayerProjectile()
{
	return &m_redProjectileSprite;
}

/*************************************************************************
Name: getWandPickupSprite()
Description : gets the sprite for the wand pickup
Parameters: None
Returns: sf::Sprite pointer
Author : Jayden Burns
**************************************************************************/
sf::Sprite* cGameManager::getWandPickupSprite()
{
	return &m_wandPickupSprite;
}

/*************************************************************************
Name: AddToCollisionList
Description : Takes a character reference and adds them to the vector of characters used in our collision
Parameters: Character reference to a specific character
Returns: None
Author : Jayden Burns
**************************************************************************/
void cGameManager::AddToCollisionList(cCharacter* _Character)
{
	m_CollisionList->push_back(_Character);
}

/*************************************************************************
Name: GetFromCollisionList
Description : Takes an int index and returns the character reference at that index of the collision list
Parameters: int value, will be the index in which to access the collision list
Returns: Character reference
Author : Jayden Burns
**************************************************************************/
cCharacter* cGameManager::GetFromCollisionList(int _ListPosition)
{
	return m_CollisionList->at(_ListPosition);
}

/*************************************************************************
Name: getCollisionList
Description : gets the reference to the collision list
Parameters: None
Returns: Pointer to the vector of character pointers
Author : Jayden Burns
**************************************************************************/
std::vector<cCharacter*>* cGameManager::getCollisionList()
{
	return m_CollisionList;
}

/*************************************************************************
Name: getProjectilesList
Description : gets the reference to the projectiles list
Parameters: None
Returns: Pointer to the vector of projectile pointers
Author : Daniel Kilfoyle
**************************************************************************/
std::vector<cProjectile*>* cGameManager::getProjectilesList()
{
	return m_ProjectileList;
}

void cGameManager::SetupEnemySprites()
{
	// Enemy Sprites
	m_asteroidTexture.loadFromFile("Resources/Textures/Sprites/EnemyAsteroid.png");
	m_asteroidEnemySprite.setTexture(m_asteroidTexture);

	m_randomEnemyTexture.loadFromFile("Resources/Textures/Sprites/EnemyRandom.png");
	m_randomEnemySprite.setTexture(m_randomEnemyTexture);

	m_chaseEnemyTexture.loadFromFile("Resources/Textures/Sprites/EnemyChase.png");
	m_chaseEnemySprite.setTexture(m_chaseEnemyTexture);

	m_defaultEnemyTexture.loadFromFile("Resources/Textures/Sprites/EnemyDefault.png");
	m_defaultEnemySprite.setTexture(m_defaultEnemyTexture);

	m_testEnemy1Texture.loadFromFile("Resources/Textures/Enemy/AnimTest_1.png");
	m_TestSprite1.setTexture(m_testEnemy1Texture);

	m_testEnemy2Texture.loadFromFile("Resources/Textures/Enemy/AnimTest_2.png");
	m_TestSprite2.setTexture(m_testEnemy2Texture);	

	m_testEnemy1Texture.loadFromFile("Resources/Textures/Enemy/AnimTest_3.png");
	m_TestSprite1.setTexture(m_testEnemy1Texture);	

	m_testEnemy4Texture.loadFromFile("Resources/Textures/Enemy/AnimTest_4.png");
	m_TestSprite4.setTexture(m_testEnemy4Texture);
}

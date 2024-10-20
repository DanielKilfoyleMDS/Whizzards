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
	LoadSprite(&m_firstPlayerSprite,&m_firstPlayerTexture,"Resources/Textures/Sprites/Blue Player.png");
	LoadSprite(&m_secondPlayerSprite,&m_secondPlayerTexture,"Resources/Textures/Sprites/Red Player.png");

	//Player Projectiles
	LoadSprite(&m_blueProjectileSprite,&m_blueProjectileTexture,"Resources/Textures/Sprites/Projectile Blue.png");
	LoadSprite(&m_redProjectileSprite,&m_redProjectileTexture,"Resources/Textures/Sprites/Projectile Red.png");

	//Pickups
	LoadSprite(&m_wandPickupSprite,&m_wandPickupTexture,"Resources/Textures/Sprites/wandpickup.png");

}

void cGameManager::LoadSprite(sf::Sprite* _Sprite, sf::Texture* _Texture, const std::string& _FilePath)
{
	_Texture->loadFromFile(_FilePath);
	_Sprite->setTexture(*_Texture);

	// Ensure the texture is loaded before setting the origin
	if (_Sprite->getTexture() != nullptr) {
		auto textureSize = _Sprite->getTexture()->getSize();
		_Sprite->setOrigin(textureSize.x / 2.f, textureSize.y / 2.f);
	}
	else {
		std::cerr << "Texture not set for sprite, cannot set origin." << std::endl;
		return; // Handle the error accordingly
	}
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
Parameters: int _frame
Returns: sf::Sprite pointer
Author : Daniel Kilfoyle
**************************************************************************/
sf::Sprite* cGameManager::getFirstPlayerSprite(int _frame)
{
	//Code To Choose Sprite Based on Frame Here!
	return &m_firstPlayerSprite;
}

/*************************************************************************
Name: getSecondPlayerSprite
Description : gets the sprite for the second player
Parameters: int _frame
Returns: sf::Sprite pointer
Author : Daniel Kilfoyle
**************************************************************************/
sf::Sprite* cGameManager::getSecondPlayerSprite(int _frame)
{
	//Code To Choose Sprite Based on Frame Here!
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

	LoadSprite(&m_asteroidEnemySprite, &m_asteroidTexture, "Resources/Textures/Sprites/EnemyAsteroid.png");
	LoadSprite(&m_randomEnemySprite, &m_randomEnemyTexture, "Resources/Textures/Sprites/EnemyRandom.png");
	LoadSprite(&m_chaseEnemySprite, &m_chaseEnemyTexture, "Resources/Textures/Sprites/EnemyChase.png");

	LoadSprite(&m_defaultEnemySprite, &m_defaultEnemyTexture, "Resources/Textures/Sprites/EnemyDefault.png");

	LoadSprite(&m_TestSprite1, &m_testEnemy1Texture, "Resources/Textures/Enemy/AnimTest_1.png");
	LoadSprite(&m_TestSprite2, &m_testEnemy2Texture, "Resources/Textures/Enemy/AnimTest_2.png");
	LoadSprite(&m_TestSprite3, &m_testEnemy3Texture, "Resources/Textures/Enemy/AnimTest_3.png");
	LoadSprite(&m_TestSprite4, &m_testEnemy4Texture, "Resources/Textures/Enemy/AnimTest_4.png");

}

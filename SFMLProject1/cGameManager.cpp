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
	SetupProjectileSprites();

	SetupPlayerSprites();

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
sf::Sprite* cGameManager::getEnemyChaseSprite(int _Frame)
{
	if (_Frame == 0)
	{
		return  &m_chaseEnemySprite1;
	}
	else if (_Frame == 1)
	{
		return  &m_chaseEnemySprite2;
	}
	else if (_Frame == -1)
	{
		return &m_chaseEnemySpriteHurt;
	}
	else
	{
		return  &m_chaseEnemySprite3;
	}
}

/*************************************************************************
Name: getEnemyRandomSprite
Description : gets the sprite for the random enemy type
Parameters: None
Returns: sf::Sprite pointer
Author : Daniel Kilfoyle
**************************************************************************/
sf::Sprite* cGameManager::getEnemyRandomSprite(int _Frame)
{
	if (_Frame == 0)
	{
		return &m_randomEnemySprite1;
	}else if (_Frame == 1)
	{
			return &m_randomEnemySprite2;
	}else if (_Frame == -1)
	{
			return &m_randomEnemySpriteHurt;
	} else
	{
		return &m_randomEnemySprite3;
	}

	return nullptr;
}

/*************************************************************************
Name: getFirstPlayerSprite
Description : gets the sprite for the first player
Parameters: int _frame
Returns: sf::Sprite pointer
Author : Daniel Kilfoyle & Jayden Burns
**************************************************************************/
sf::Sprite* cGameManager::getFirstPlayerSprite(int _frame)
{
	//Code To Choose Sprite Based on Frame Here!
	if (_frame == 0)
	{
		return &m_firstPlayerForwardSprite;
	}
	else if (_frame == 1)
	{
		return &m_firstPlayerLeftSprite;
	}
	else if (_frame == 2)
	{
		return &m_firstPlayerRightSprite;
	}

	return &m_firstPlayerForwardSprite;
}

/*************************************************************************
Name: getSecondPlayerSprite
Description : gets the sprite for the second player
Parameters: int _frame
Returns: sf::Sprite pointer
Author : Daniel Kilfoyle & Jayden Burns
**************************************************************************/
sf::Sprite* cGameManager::getSecondPlayerSprite(int _frame)
{
	if (_frame == 0)
	{
		return &m_secondPlayerForwardSprite;
	}
	else if (_frame == 1)
	{
		return &m_secondPlayerLeftSprite;
	}
	else if (_frame == 2)
	{
		return &m_secondPlayerRightSprite;
	}

	return &m_secondPlayerForwardSprite;
}

sf::Sprite* cGameManager::getPlayerInvincSprite()
{
	return &m_playerInvincibleSprite;
}

/*************************************************************************
Name: getFirstPlayerProjectile
Description : gets the sprite for the first player's projectiles
Parameters: None
Returns: sf::Sprite pointer
Author : Daniel Kilfoyle
**************************************************************************/
sf::Sprite* cGameManager::getFirstPlayerProjectile(int _frame)
{
	//Code To Choose Sprite Based on Frame Here!
	return &m_blueProjectileSprite;
}

/*************************************************************************
Name: getSecondPlayerProjectile
Description : gets the sprite for the second player's projectiles
Parameters: None
Returns: sf::Sprite pointer
Author : Daniel Kilfoyle
**************************************************************************/
sf::Sprite* cGameManager::getSecondPlayerProjectile(int _frame)
{
	//Code To Choose Sprite Based on Frame Here!
	return &m_redProjectileSprite;
}

/*************************************************************************
Name: getFireProjectile
Description : gets the sprite for the Fire Type projectiles
Parameters: None
Returns: sf::Sprite pointer
Author : JaydenBurns
**************************************************************************/
sf::Sprite* cGameManager::getFireProjectile(int _frame)
{
	if (_frame == 0)
	{
		return &m_FireProjSprite1;
	}
	else if (_frame == 1)
	{
		return &m_FireProjSprite2;
	}
	else if (_frame == 2)
	{
		return &m_FireProjSprite3;
	}
	else if (_frame == 3)
	{
		return &m_FireProjSprite4;
	}
	else
	{
		return &m_FireProjSprite5;
	}
}


/*************************************************************************
Name: getWandPickupSprite()
Description : gets the sprite for the wand pickup
Parameters: None
Returns: sf::Sprite pointer
Author : Jayden Burns
**************************************************************************/
sf::Sprite* cGameManager::getWandPickupSprite(int _frame)
{
	//Code To Choose Sprite Based on Frame Here!
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
	LoadSprite(&m_randomEnemySprite1, &m_randomEnemyTexture1, "Resources/Textures/Sprites/EnemyRandom1.png");
	LoadSprite(&m_randomEnemySprite2, &m_randomEnemyTexture2, "Resources/Textures/Sprites/EnemyRandom2.png");
	LoadSprite(&m_randomEnemySprite3, &m_randomEnemyTexture3, "Resources/Textures/Sprites/EnemyRandom3.png");
	LoadSprite(&m_chaseEnemySprite1, &m_chaseEnemyTexture1, "Resources/Textures/Sprites/EnemyChase.png");
	LoadSprite(&m_chaseEnemySprite2, &m_chaseEnemyTexture2, "Resources/Textures/Sprites/EnemyChase2.png");
	LoadSprite(&m_chaseEnemySprite3, &m_chaseEnemyTexture3, "Resources/Textures/Sprites/EnemyChase3.png");

	LoadSprite(&m_chaseEnemySpriteHurt, &m_chaseEnemyTextureHurt, "Resources/Textures/Sprites/EnemyChaseHurt2.png");
	LoadSprite(&m_randomEnemySpriteHurt, &m_randomEnemyTextureHurt, "Resources/Textures/Sprites/EnemyRandomHurt2.png");

	LoadSprite(&m_shootEnemySprite, &m_shootEnemyTexture, "Resources/Textures/Sprites/EnemyProjectile.png");

	LoadSprite(&m_defaultEnemySprite, &m_defaultEnemyTexture, "Resources/Textures/Sprites/EnemyDefault.png");

}

void cGameManager::SetupProjectileSprites()
{
	LoadSprite(&m_FireProjSprite1, &m_FireProjTex1, "Resources/Textures/Sprites/FProjA.png");
	LoadSprite(&m_FireProjSprite2, &m_FireProjTex2, "Resources/Textures/Sprites/FProjB.png");
	LoadSprite(&m_FireProjSprite3, &m_FireProjTex3, "Resources/Textures/Sprites/FProjC.png");
	LoadSprite(&m_FireProjSprite4, &m_FireProjTex4, "Resources/Textures/Sprites/FProjD.png");
	LoadSprite(&m_FireProjSprite5, &m_FireProjTex5, "Resources/Textures/Sprites/FProjE.png");
}

void cGameManager::SetupPlayerSprites()
{
	// Player Sprites
	LoadSprite(&m_firstPlayerForwardSprite, &m_firstPlayerForwardTexture, "Resources/Textures/Sprites/whizzardAF.png");
	LoadSprite(&m_firstPlayerRightSprite, &m_firstPlayerRightTexture, "Resources/Textures/Sprites/whizzardAR.png");
	LoadSprite(&m_firstPlayerLeftSprite, &m_firstPlayerLeftTexture, "Resources/Textures/Sprites/whizzardAL.png");
	LoadSprite(&m_secondPlayerForwardSprite, &m_secondPlayerForwardTexture, "Resources/Textures/Sprites/whizzardBF.png");
	LoadSprite(&m_secondPlayerRightSprite, &m_secondPlayerRightTexture, "Resources/Textures/Sprites/whizzardBR.png");
	LoadSprite(&m_secondPlayerLeftSprite, &m_secondPlayerLeftTexture, "Resources/Textures/Sprites/whizzardBL.png");
	LoadSprite(&m_playerInvincibleSprite, &m_playerInvincibleTexture, "Resources/Textures/Sprites/Shield.png");
}

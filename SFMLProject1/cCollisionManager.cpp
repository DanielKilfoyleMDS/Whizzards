/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : cCollisionManager.cpp
Description : The manager class for all of the collisions in game
Author : Daniel Kilfoyle
Mail : DanielKilfoyle@mds.ac.nz
**************************************************************************/

#include "cCollisionManager.h"

/*************************************************************************
Name: cCollisionManager
Description : constructor for the collision manager
Parameters: None
Returns: None
Author : Daniel Kilfoyle
**************************************************************************/
cCollisionManager::cCollisionManager()
{
}

/*************************************************************************
Name: collisionCheck
Description : iterates through the vector of all active characters, and checks if they are colliding. Runs relevant events accordingly
Parameters: vector<cCharacter*> active characters
Returns: None
Author : Daniel Kilfoyle
**************************************************************************/
void cCollisionManager::collisionCheck(std::vector<cCharacter*> _activeCharacters)
{
	//for (int i = 0; i < _activeCharacters.size(); i++)
	//{
	//	for (int j = 0; j < _activeCharacters.size(); j++)
	//	{
	//		if (_activeCharacters[i] == _activeCharacters[j])
	//		{
	//			// Cannot collide with self.
	//			// Do nothing
	//			break;
	//		}
	//		else 
	//		{

	//			float xStart = _activeCharacters[i]->getPosition().x + (_activeCharacters[i]->getSprite()->getTexture()->getSize().x / 2);
	//			float yStart = _activeCharacters[i]->getPosition().y + (_activeCharacters[i]->getSprite()->getTexture()->getSize().y / 2);
	//			float xBounds = _activeCharacters[i]->getSprite()->getTexture()->getSize().x;
	//			float yBounds = _activeCharacters[i]->getSprite()->getTexture()->getSize().y;
	//			sf::FloatRect firstcollider(xStart, yStart, xBounds, yBounds);


	//			xStart = _activeCharacters[j]->getPosition().x + (_activeCharacters[j]->getSprite()->getTexture()->getSize().x / 2);
	//			yStart = _activeCharacters[j]->getPosition().y + (_activeCharacters[j]->getSprite()->getTexture()->getSize().y / 2);
	//			xBounds = _activeCharacters[j]->getSprite()->getTexture()->getSize().x;
	//			yBounds = _activeCharacters[j]->getSprite()->getTexture()->getSize().y;
	//			sf::FloatRect secondcollider(xStart, yStart, xBounds, yBounds);



	//			// Checking if the characters are overlapping, then processing what happens with the collision afterwards
	//			if (firstcollider.intersects(secondcollider))
	//			{

	//				// _activeCharacters[j]->getSprite()_activeCharacters[j]->getSprite()->getGlobalBounds()
	//				// Checks for specific character types 

	//				if (_activeCharacters[i]->getCharacterType() == Player)
	//				{
	//					if (_activeCharacters[j]->getCharacterType() == Player) // Checking if the players have collided
	//					{
	//						// Deal damage to both players
	//						_activeCharacters[i]->updateHealth(-10.0f);
	//						_activeCharacters[j]->updateHealth(-10.0f);
	//			
	//						// Move both players backward from the collision location. 
	//						// Calculate the amount the first player will be pushed backward
	//						sf::Vector2f newPos(-30.0f * sin(DegreesToRadians(_activeCharacters[i]->getRotation())), 30.0f * cos(DegreesToRadians(_activeCharacters[i]->getRotation())));
	//						// Move the first player backward.
	//						_activeCharacters[i]->setPosition(_activeCharacters[i]->getPosition() + newPos);
	//			
	//						/// Move the second player in the direction the first player was moving
	//						_activeCharacters[j]->setPosition(_activeCharacters[j]->getPosition() - newPos);

	//						std::cout << "BONK!!" << std::endl;
	//					}
	//					else if (_activeCharacters[j]->getCharacterType() == Enemy)
	//					{
	//						// Deal damage to the player
	//						std::cout << "Player i - enemy j - Damage" << std::endl;

	//						// Colliding enemy
	//						cEnemy* collidingEnemy = dynamic_cast<cEnemy*>(_activeCharacters[j]);
	//						collidingEnemy->otherCollide(_activeCharacters[i]);
	//						
	//					}
	//				}
	//				// If the first character type is enemy, and colliding character is a player
	//				else if (_activeCharacters[i]->getCharacterType() == Enemy)
	//				{
	//					if (_activeCharacters[j]->getCharacterType() == Player)
	//					{

	//						// Deal damage to the player
	//						std::cout << "enemy i - Player j - Damage" << std::endl;

	//						// Colliding enemy
	//						cEnemy* collidingEnemy = dynamic_cast<cEnemy*>(_activeCharacters[i]);
	//						
	//						if (collidingEnemy->getAwake())
	//						{
	//							collidingEnemy->otherCollide(_activeCharacters[j]);
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
}

/*************************************************************************
Name: projectileCheck
Description : checks the vector of projectiles against the vector of characters and whether they collide
Parameters: vector<cCharacter*> - characters, vector<cProjectile*> - projectiles
Returns: None
Author : Daniel Kilfoyle
**************************************************************************/
void cCollisionManager::projectileCheck(std::vector<cCharacter*> _activeCharacters, std::vector<cProjectile*> _activeProjectiles)
{
	//for (int proj = 0; proj < _activeProjectiles.size(); proj++)
	//{
	//	for (int i = 0; i < _activeCharacters.size(); i++)
	//	{
	//		float xStart = _activeCharacters[i]->getPosition().x - (_activeCharacters[i]->getSprite()->getTexture()->getSize().x / 2);
	//		float yStart = _activeCharacters[i]->getPosition().y - (_activeCharacters[i]->getSprite()->getTexture()->getSize().y / 2);
	//		float xBounds = _activeCharacters[i]->getSprite()->getTexture()->getSize().x;
	//		float yBounds = _activeCharacters[i]->getSprite()->getTexture()->getSize().y;
	//		sf::FloatRect firstcollider(xStart, yStart, xBounds, yBounds);

	//		sf::Sprite projSprite = *_activeProjectiles[proj]->getSprite();
	//		if (projSprite.getGlobalBounds().intersects(firstcollider))
	//		{
	//			if (!_activeProjectiles[proj]->getOwned())
	//			{
	//				if (_activeCharacters[i]->getCharacterType() == Enemy)
	//				{
	//					// If the projectile belongs to a player, and it intersects with an enemy, then deal damage to the enemy
	//					_activeCharacters[i]->updateHealth(_activeProjectiles[proj]->getDamage());
	//					std::cout << "Enemy damaged! Remaining health: " << _activeCharacters[i]->getHealth() << std:: endl;

	//					break;
	//					
	//				}
	//			}
	//		}
	//	}
	//	
	//}
}

void cCollisionManager::wandCheck(std::vector <cCharacter*> _activeCharacters, std::vector<cWandPickup*> _wandPickups)
{
	//for (int wand = 0; wand < _wandPickups.size(); wand++)
	//{
	//	for (int character = 0; character < _activeCharacters.size(); character++)
	//	{
	//		if (_wandPickups[wand]->getSprite()->getGlobalBounds().intersects(_activeCharacters[character]->getSprite()->getGlobalBounds()))
	//		{
	//			if (_activeCharacters[character]->getCharacterType() == Player)
	//			{
	//				// Pick up wand and set

	//				cPlayer* collidingPlayer = dynamic_cast<cPlayer*> (_activeCharacters[character]);
	//				_wandPickups[wand]->playerCollision(collidingPlayer);

	//				std::cout << "Wand picked up" << std::endl;
	//			}
	//		}
	//	}
	//}
}


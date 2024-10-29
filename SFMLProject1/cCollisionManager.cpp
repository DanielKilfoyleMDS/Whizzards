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
	for (int i = 0; i < _activeCharacters.size(); i++)
	{
		for (int j = 0; j < _activeCharacters.size(); j++)
		{
			if (_activeCharacters[i] == _activeCharacters[j])
			{
				// Cannot collide with self.
				// Do nothing
				break;
			}
			else 
			{

				float xStart = _activeCharacters[i]->getPosition().x;
				float yStart = _activeCharacters[i]->getPosition().y;
				float xBounds = _activeCharacters[i]->getHitbox().x;
				float yBounds = _activeCharacters[i]->getHitbox().y;
				sf::FloatRect firstcollider(xStart, yStart, xBounds, yBounds);

				


				xStart = _activeCharacters[j]->getPosition().x;
				yStart = _activeCharacters[j]->getPosition().y;
				xBounds = _activeCharacters[j]->getHitbox().x;
				yBounds = _activeCharacters[j]->getHitbox().y;
				sf::FloatRect secondcollider(xStart, yStart, xBounds, yBounds);



				// Checking if the characters are overlapping, then processing what happens with the collision afterwards
				if (firstcollider.intersects(secondcollider))
				{

					// Checks for specific character types 

					if (_activeCharacters[i]->getCharacterType() == Player)
					{
						if (_activeCharacters[j]->getCharacterType() == Player) // Checking if the players have collided
						{
							// Deal damage to both players
							_activeCharacters[i]->updateHealth(-10.0f);
							_activeCharacters[j]->updateHealth(-10.0f);
				
							// Move both players backward from the collision location. 
							// Calculate the amount the first player will be pushed backward
							sf::Vector2f newPos(-30.0f * sin(DegreesToRadians(_activeCharacters[i]->getRotation())), 30.0f * cos(DegreesToRadians(_activeCharacters[i]->getRotation())));
							// Move the first player backward.
							_activeCharacters[i]->setPosition(_activeCharacters[i]->getPosition() + newPos);
				
							/// Move the second player in the direction the first player was moving
							_activeCharacters[j]->setPosition(_activeCharacters[j]->getPosition() - newPos);

							std::cout << "BONK!!" << std::endl;

							
							if (_activeCharacters[j]->getDamageSound()->getStatus() == sf::SoundSource::Playing)
							{
								// do nothing
							}
							else
							{
								// Play the damage sound, since it was not previously playing
								_activeCharacters[j]->getDamageSound()->play();
							}
						}
						else if (_activeCharacters[j]->getCharacterType() == Enemy)
						{
							// Deal damage to the player
							std::cout << "Player i - enemy j - Damage" << std::endl;



							// Colliding enemy
							cEnemy* collidingEnemy = dynamic_cast<cEnemy*>(_activeCharacters[j]);
							collidingEnemy->otherCollide(_activeCharacters[i]);


							
						}
					}
					// If the first character type is enemy, and colliding character is a player
					else if (_activeCharacters[i]->getCharacterType() == Enemy)
					{
						if (_activeCharacters[j]->getCharacterType() == Player)
						{

							// Deal damage to the player
							std::cout << "enemy i - Player j - Damage" << std::endl;

							// Colliding enemy
							cEnemy* collidingEnemy = dynamic_cast<cEnemy*>(_activeCharacters[i]);
							
							if (collidingEnemy->getAwake())
							{
								collidingEnemy->otherCollide(_activeCharacters[j]);
								// Colliding player
								std::cout << "Damage sound" << std::endl;
								if (_activeCharacters[j]->getDamageSound()->getStatus() == sf::SoundSource::Playing)
								{
									// do nothing
								}
								else
								{
									_activeCharacters[j]->getDamageSound()->play();
								}
							}


							
						}
					}
				}
			}
		}
	}
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
	for (int proj = 0; proj < _activeProjectiles.size(); proj++)
	{
		for (int i = 0; i < _activeCharacters.size(); i++)
		{
			float xStart = _activeCharacters[i]->getPosition().x;
			float yStart = _activeCharacters[i]->getPosition().y;
			float xBounds = _activeCharacters[i]->getHitbox().x;
			float yBounds = _activeCharacters[i]->getHitbox().y;
			sf::FloatRect firstcollider(xStart, yStart, xBounds, yBounds);

			xStart = _activeProjectiles[proj]->getPosition().x;
			yStart = _activeProjectiles[proj]->getPosition().y;
			xBounds = _activeProjectiles[proj]->getHitbox().x;
			yBounds = _activeProjectiles[proj]->getHitbox().y;
			sf::FloatRect secondcollider(xStart, yStart, xBounds, yBounds);

			if (secondcollider.intersects(firstcollider))
			{
				if (!_activeProjectiles[proj]->getOwned())
				{
					if (_activeCharacters[i]->getCharacterType() == Enemy)
					{
						// If the projectile belongs to a player, and it intersects with an enemy, then deal damage to the enemy
						_activeCharacters[i]->applyDamage(_activeProjectiles[proj]->getDamage());
						std::cout << "Enemy damaged! Remaining health: " << _activeCharacters[i]->getHealth() << std:: endl;
						
						// Check if the projectile hit sound is already playing
						if (_activeCharacters[i]->getProjectileHitSound()->getStatus() == sf::SoundSource::Playing)
						{
							// do nothing since the sound is already playing
						}
						else
						{
							// play the sound, since it was not previously
							_activeCharacters[i]->getProjectileHitSound()->play();
						}
						break;
						
					}
				}
				else if (_activeProjectiles[proj]->getOwned())
				{
					if (_activeCharacters[i]->getCharacterType() == Player)
					{
						// If the projectile belongs to an enemy, and it intersects with a player then deal damage to the player
						_activeCharacters[i]->applyDamage(_activeProjectiles[proj]->getDamage());
						std::cout << "Player damaged! Remaining health: " << _activeCharacters[i]->getHealth() << std::endl;

						// Check if the projectile hit sound is already playing
						if (_activeCharacters[i]->getProjectileHitSound()->getStatus() == sf::SoundSource::Playing)
						{
							// do nothing since the sound is already playing
						}
						else
						{
							// play the sound, since it was not previously
							_activeCharacters[i]->getProjectileHitSound()->play();
						}
						break;

					}
				}

			}
		}
		
	}
}

void cCollisionManager::wandCheck(std::vector <cCharacter*> _activeCharacters, std::vector<cWandPickup*> _wandPickups)
{
	for (int wand = 0; wand < _wandPickups.size(); wand++)
	{
		for (int character = 0; character < _activeCharacters.size(); character++)
		{
			float xStart = _activeCharacters[character]->getPosition().x;
			float yStart = _activeCharacters[character]->getPosition().y;
			float xBounds = _activeCharacters[character]->getHitbox().x;
			float yBounds = _activeCharacters[character]->getHitbox().y;
			sf::FloatRect firstcollider(xStart, yStart, xBounds, yBounds);

			xStart = _wandPickups[wand]->getPosition().x;
			yStart = _wandPickups[wand]->getPosition().y;
			xBounds = _wandPickups[wand]->getHitbox().x;
			yBounds = _wandPickups[wand]->getHitbox().y;
			sf::FloatRect secondcollider(xStart, yStart, xBounds, yBounds);

			if (secondcollider.intersects(firstcollider))
			{
				if (_activeCharacters[character]->getCharacterType() == Player)
				{
					// Pick up wand and set

					cPlayer* collidingPlayer = dynamic_cast<cPlayer*> (_activeCharacters[character]);
					_wandPickups[wand]->playerCollision(collidingPlayer);

					std::cout << "Wand picked up" << std::endl;
				}
			}
		}
	}
}


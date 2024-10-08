#include "cCollisionManager.h"

cCollisionManager::cCollisionManager()
{
}

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
			}
			else 
			{
				// Checking if the characters are overlapping, then processing what happens with the collision afterwards
				if (_activeCharacters[i]->getSprite()->getGlobalBounds().intersects(_activeCharacters[j]->getSprite()->getGlobalBounds()))
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
							sf::Vector2f newPos(-10.0f * sin(DegreesToRadians(_activeCharacters[i]->getRotation())), 10.0f * cos(DegreesToRadians(_activeCharacters[i]->getRotation())));
							// Move the first player backward.
							_activeCharacters[i]->setPosition(_activeCharacters[i]->getPosition() + newPos);

							// Recalculate the new position for the second player
							newPos = sf::Vector2f(-10.0f * sin(DegreesToRadians(_activeCharacters[j]->getRotation())), 10.0f * cos(DegreesToRadians(_activeCharacters[j]->getRotation())));
							// Move the second player backward.
							_activeCharacters[j]->setPosition(_activeCharacters[j]->getPosition() + newPos);

							std::cout << "Player on player!!" << std::endl;
						}
						else if (_activeCharacters[j]->getCharacterType() == Enemy)
						{
							// Deal damage to the player
							std::cout << "DAMAGE PLAYER" << std::endl;
						}
					}

					
				}
			}
		}
	}
}

void cCollisionManager::projectileCheck(std::vector<cCharacter*> _activeCharacters, std::vector<cProjectile*> _activeProjectiles)
{
	
}

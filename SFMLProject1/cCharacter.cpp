#include "cCharacter.h"

cCharacter::cCharacter(std::string _FilePath, std::string _CharacterName, sf::Vector2f _StartPosition)
{
	// TODO - set from pointer in game manager class
	setSprite(_FilePath);

	characterSprite.setOrigin(characterTexture.getSize().x / 2, characterTexture.getSize().y / 2);
	characterPosition = _StartPosition;
	characterSprite.setPosition(characterPosition);

	// TODO - remove as characte name is not necessary
	characterName = _CharacterName;

}

void cCharacter::setHealth(float _Health)
{
	// TODO - Variable names
	currentHealth = _Health;
	healthCheck();
}

void cCharacter::takeDamage(float _Damage)
{
	// TODO - Variable names
	currentHealth -= _Damage;
	healthCheck();
}

void cCharacter::restoreHealth(float _Healing)
{
	// TODO - Variable names
	currentHealth += _Healing; 
	healthCheck();
}

void cCharacter::healthCheck()
{
	// TODO - Will be changed when update health is modified

	// Check if the character health has gone above its maximum, and set the value to the maximum instead.
	if (currentHealth > MAX_HEALTH)
	{
		currentHealth = MAX_HEALTH;
	}

	// Check if health has reached or gone below 0, then call appropriate death function for the 
	else if (currentHealth <= 0)
	{
		// run death functions
	}

	// Return in all other cases, when health is in the intended range (Above 0 and less than or equal to maximum)
	else
		return;
}
// TODO - Keep set sprite for enemies
// TODO - pass in reference to sprite not file path
void cCharacter::setSprite(std::string _FilePath)
{
	characterTexture.loadFromFile(_FilePath);
	characterSprite.setTexture(characterTexture);
}


// TODO - being moved to player
void cCharacter::rotateCharacter(int _Direction)
{
	// Left rotation if the direction was given as negative, right rotation if the direction was positive
	int rotationDirection = 0;
	if (_Direction < 0) { rotationDirection = -1;}
	else if (_Direction > 0){ rotationDirection = 1;}

	characterRotation += rotationDirection * 5.0f;
	characterSprite.setRotation(characterRotation);
	convertRotation();


}

// TODO - Remove. Will be in math library
void cCharacter::convertRotation()
{
	//radiansRotation = characterRotation * (M_PI / 180);
}

// TODO - Can probably remove or make virtual, as child classes will have their own 
void cCharacter::moveCharacter()
{
	characterSprite.move(SPEED_SCALAR * sin(radiansRotation), SPEED_SCALAR * -cos(radiansRotation));
	//SetPosition(sf::Vector2f(characterPosition + (SPEED_SCALAR * sin(radiansRotation), SPEED_SCALAR * -cos(radiansRotation))));
}

// TODO - return pointer to sprite
sf::Sprite cCharacter::GetSprite()
{
	return characterSprite;
}

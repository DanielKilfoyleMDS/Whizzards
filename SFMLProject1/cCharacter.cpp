#include "cCharacter.h"

cCharacter::cCharacter(std::string _FilePath, std::string _CharacterName, sf::Vector2f _StartPosition)
{
	setSprite(_FilePath);
	characterSprite.setOrigin(characterTexture.getSize().x / 2, characterTexture.getSize().y / 2);
	characterPosition = _StartPosition;
	characterSprite.setPosition(characterPosition);

	characterName = _CharacterName;

}

void cCharacter::setHealth(float _Health)
{
	currentHealth = _Health;
	healthCheck();
}

void cCharacter::takeDamage(float _Damage)
{
	currentHealth -= _Damage;
	healthCheck();
}

void cCharacter::restoreHealth(float _Healing)
{
	currentHealth += _Healing; 
	healthCheck();
}

void cCharacter::healthCheck()
{
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

void cCharacter::setSprite(std::string _FilePath)
{
	characterTexture.loadFromFile(_FilePath);
	characterSprite.setTexture(characterTexture);
}



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

void cCharacter::convertRotation()
{
	//radiansRotation = characterRotation * (M_PI / 180);
}

void cCharacter::moveCharacter()
{
	characterSprite.move(SPEED_SCALAR * sin(radiansRotation), SPEED_SCALAR * -cos(radiansRotation));
	//SetPosition(sf::Vector2f(characterPosition + (SPEED_SCALAR * sin(radiansRotation), SPEED_SCALAR * -cos(radiansRotation))));
}

#include "cCharacter.h"

cCharacter::cCharacter(sf::Sprite _sprite, sf::Vector2f _StartPosition)
{

	m_characterSprite = _sprite;
	m_characterSprite.setOrigin(m_characterSprite.getTexture()->getSize().x / 2, m_characterSprite.getTexture()->getSize().y / 2);
	m_characterPosition = _StartPosition;
	m_characterSprite.setPosition(m_characterPosition);



}

void cCharacter::setHealth(float _Health)
{
	
	m_fcurrentHealth = _Health;
	healthCheck();
}

float cCharacter::getHealth()
{
	return m_fcurrentHealth;
}

void cCharacter::updateHealth(float _Change)
{
	m_fcurrentHealth += _Change;
	healthCheck();
}

void cCharacter::healthCheck()
{
	// TODO - Will be changed when update health is modified

	// Check if the character health has gone above its maximum, and set the value to the maximum instead.
	if (m_fcurrentHealth > m_fmaxHealth)
	{
		m_fcurrentHealth = m_fmaxHealth;
	}

	// Check if health has reached or gone below 0, then call appropriate death function for the 
	else if (m_fcurrentHealth <= 0)
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
	m_characterTexture.loadFromFile(_FilePath);
	m_characterSprite.setTexture(m_characterTexture);
}

void cCharacter::setRotation(float _Rotation)
{
	m_fcharacterRotation = _Rotation;
}

float cCharacter::getRotation()
{
	return m_fcharacterRotation;
}


void cCharacter::moveCharacter()
{
	m_characterSprite.move(SPEED_SCALAR * sin(m_fradiansRotation), SPEED_SCALAR * -cos(m_fradiansRotation));
}


// DONE - return pointer to sprite
sf::Sprite cCharacter::getSprite()
{
	return m_characterSprite;
}

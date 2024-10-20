/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : cCharacter.cpp
Description : Base character class. Is the parent class for enemies and players. Contains all methods that are needed by both child classes
Author : Daniel Kilfoyle & Jayden Burns
Mail : DanielKilfoyle@mds.ac.nz & JaydenBurns@mds.ac.nz
**************************************************************************/


#include "cCharacter.h"


/*************************************************************************
Name: cCharacter
Description : constructors the base character class
Parameters: sf::sprite - character sprite,  sf::vector2f - start position
Returns: None
Author : Daniel Kilfoyle
**************************************************************************/
cCharacter::cCharacter(sf::Sprite* _sprite, sf::Vector2f _StartPosition)
{
	m_characterSprite = _sprite;

	// Ensure the texture is loaded before setting the origin
	if (m_characterSprite->getTexture() != nullptr) {
		auto textureSize = m_characterSprite->getTexture()->getSize();
		m_characterSprite->setOrigin(textureSize.x / 2.f, textureSize.y / 2.f);
	}
	else {
		std::cerr << "Texture not set for sprite, cannot set origin." << std::endl;
		return; // Handle the error accordingly
	}

	m_characterPosition = _StartPosition;
	m_characterSprite->setPosition(m_characterPosition);

	m_fmaxHealth = 100;

	m_fcurrentHealth = m_fmaxHealth;
	m_fcharacterRotation = 0.0f;
	m_fradiansRotation = 0.0f;


}

/*************************************************************************
Name: setHealth
Description : sets a character's health to the input value, then runs the health check
Parameters: float - health
Returns: None
Author : Daniel Kilfoyle
**************************************************************************/
void cCharacter::setHealth(float _Health)
{
	
	m_fcurrentHealth = _Health;
	healthCheck();
}

/*************************************************************************
Name: getHealth
Description : gets a character's current health
Parameters: None
Returns: float - current health
Author : Daniel Kilfoyle
**************************************************************************/
float cCharacter::getHealth()
{
	return m_fcurrentHealth;
}

/*************************************************************************
Name: updateHealth
Description : updates the character's health by adding the change value to their current health
Parameters: float - healthChange
Returns: None
Author : Daniel Kilfoyle
**************************************************************************/
void cCharacter::updateHealth(float _Change)
{
	m_fcurrentHealth += _Change;
	healthCheck();
}

/*************************************************************************
Name: healthCheck
Description : checks if the character's health is above its maximum or below minimum. Sets those values to meet the constraints
Parameters: None
Returns: None
Author : Daniel Kilfoyle
**************************************************************************/
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
		m_fcurrentHealth = 0;
		// run death functions
	}

	// Return in all other cases, when health is in the intended range (Above 0 and less than or equal to maximum)
	else
		return;
}

/*************************************************************************
Name: setSprite
Description : takes a string file path, and loads the texture from the file, then sets the character's sprite to that texture
Parameters: string pointer - file path 
Returns: None
Author : Jayden Burns
**************************************************************************/
void cCharacter::setSprite(const std::string& _FilePath)
{
	if (!m_characterTexture.loadFromFile(_FilePath)) {
		std::cerr << "Failed to load texture from " << _FilePath << std::endl;
		return; // Handle the error
	}

	m_characterSprite->setTexture(m_characterTexture);

	// Now that the texture is set, we can safely set the origin
	auto textureSize = m_characterSprite->getTexture()->getSize();
	m_characterSprite->setOrigin(textureSize.x / 2.f, textureSize.y / 2.f);
}

/*************************************************************************
Name: setSprite
Description : takes a sprite pointer and sets the character sprite to that sprite
Parameters: sf::sprite * - sprite
Returns: None
Author : Jayden Burns
**************************************************************************/
void cCharacter::setSprite(sf::Sprite* _Sprite)
{
	m_characterSprite = _Sprite;
}


/*************************************************************************
Name: setCharacterType
Description : sets the character's charactertype to the input type
Parameters: Enum - CharacterType 
Returns: None
Author : Daniel Kilfoyle
**************************************************************************/
void cCharacter::setCharacterType(CharacterType _type)
{
	m_characterType = _type;
}

/*************************************************************************
Name: getCharacterType
Description : returns the character's character type
Parameters: None
Returns: Enum - CharacterType 
Author : Daniel Kilfoyle
**************************************************************************/
CharacterType cCharacter::getCharacterType()
{
	return m_characterType;
}

/*************************************************************************
Name: setRotation
Description : sets the character rotation to the rotation input
Parameters: float - rotation value
Returns: None
Author : Daniel Kilfoyle
**************************************************************************/
void cCharacter::setRotation(float _Rotation)
{
	m_fcharacterRotation = _Rotation;
}

/*************************************************************************
Name: getRotation
Description : returns the character's rotation
Parameters: None
Returns: float - rotation
Author : Daniel Kilfoyle
**************************************************************************/
float cCharacter::getRotation()
{
	return m_fcharacterRotation;
}

/*************************************************************************
Name: moveCharacter
Description : base for character movement. Virtual function to be overridden by child classes
Parameters: None
Returns: None
Author : Daniel Kilfoyle
**************************************************************************/
void cCharacter::moveCharacter()
{
	m_characterSprite->move(SPEED_SCALAR * sin(m_fradiansRotation), SPEED_SCALAR * -cos(m_fradiansRotation));
}


/*************************************************************************
Name: getSprite
Description : returns the pointer of the character's sprite
Parameters: None
Returns: sf::Sprite* - character sprite
Author : Daniel Kilfoyle
**************************************************************************/
sf::Sprite* cCharacter::getSprite()
{
	return m_characterSprite;
}


/*************************************************************************
Name: framesPassed
Description : returns how many frames have passed due to deltaTime
Parameters: float _deltaTime
Returns: int Frames Passed
Author : Jayden Burns
**************************************************************************/
int cCharacter::framesPassed(float _deltaTime)
{
	int FramesPassed = 0;
	m_fAnimationTime += _deltaTime;
	while (m_fAnimationTime > m_fSecondsPerFrame)
	{
		m_fAnimationTime -= 1;
		FramesPassed++;
	}
	return FramesPassed;
}

int cCharacter::getFrame()
{
	return m_iCurrentFrame;
}

void cCharacter::setFrame(int _Frame)
{
	m_iCurrentFrame = _Frame;
}

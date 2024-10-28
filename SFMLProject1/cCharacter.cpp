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
	//TODO - Set Size From Sprite

	m_characterPosition = _StartPosition;

	m_fmaxHealth = 100;

	m_fcurrentHealth = m_fmaxHealth;
	m_fcharacterRotation = 0.0f;
	m_fradiansRotation = 0.0f;

	float xBounds = _sprite->getTexture()->getSize().x;
	float yBounds = _sprite->getTexture()->getSize().y;

	m_hitboxSize.x = xBounds;
	m_hitboxSize.y = yBounds;

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
	//m_characterSprite->move(SPEED_SCALAR * sin(m_fradiansRotation), SPEED_SCALAR * -cos(m_fradiansRotation));
	m_characterPosition += sf::Vector2f(SPEED_SCALAR * sin(m_fradiansRotation), SPEED_SCALAR * -cos(m_fradiansRotation));
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
		m_fAnimationTime -= m_fSecondsPerFrame;
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

bool cCharacter::applyDamage(float _Damage)
{
	if (m_fHurtTime > 0)	return false;
	else
	{
		m_fcurrentHealth -= _Damage;
		m_fHurtTime = m_fHurtMaxTime;
		return true;
	}
}

void cCharacter::handleHurt(float deltaTime)
{
	if (m_fHurtTime > 0)
	{
		m_fHurtTime -= deltaTime;
	}
}

void cCharacter::checkScreenWrap(cLevel _level)
{
	// Screen wrapping logic
	sf::Vector2f position = getPosition();
	if (position.x < 0) {
		position.x += _level.getLevelWidth();
	}
	else if (position.x > _level.getLevelWidth()) {
		position.x -= _level.getLevelWidth();
	}

	if (position.y < 0) {
		position.y += _level.getLevelHeight();
	}
	else if (position.y > _level.getLevelHeight()) {
		position.y -= _level.getLevelHeight();
	}

	setPosition(position);
}


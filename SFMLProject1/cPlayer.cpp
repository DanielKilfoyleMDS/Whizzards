/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : cPlayer.cpp
Description : player class, child of cCharacter.  Contains all methods for the player characters
Author : Daniel Kilfoyle
Mail : DanielKilfoyle@mds.ac.nz
**************************************************************************/

#include "cPlayer.h"
#include "SFML/Graphics.hpp"
#include "cWand.h"


cPlayer::cPlayer(sf::Sprite* _Sprite, std::string _PlayerName, sf::Vector2f _Position, std::vector<cCharacter*>* _activeCharacters, cLevel& _level)
	: cCharacter(_Sprite, _Position), // Call to base class constructor
	m_playerName(_PlayerName), // Initialize player name
	level(_level) // Initialize the level reference

{
	

	// Set control keys based on player name
	if (m_playerName == "Player 1") {
		leftRotateKey = sf::Keyboard::Key::A;
		rightRotateKey = sf::Keyboard::Key::D;
		forwardMovementKey = sf::Keyboard::Key::W;
		castSpellKey = sf::Keyboard::Key::S;
	}
	else if (m_playerName == "Player 2") {
		leftRotateKey = sf::Keyboard::Key::Left;
		rightRotateKey = sf::Keyboard::Key::Right;
		forwardMovementKey = sf::Keyboard::Key::Up;
		castSpellKey = sf::Keyboard::Key::Down;
	}

	// Setting the current health of a player to max, as they have yet to take damage
	m_fcurrentHealth = m_fmaxHealth;

	setCharacterType(Player);

	_activeCharacters->push_back(this);
	m_castTimer.restart();

	m_fFireRate = 1.0f;
	m_iProjectileCount = 1;
	m_fDamage = 10.0f;

	currentWandName = "Default Wand";

	m_InvincibilityTimer = 5.0f;
}

/*************************************************************************
Name: rotateCharacter
Description : rotates the character given a key for direction, and a scalar for whether they are moving already or not
Parameters: sf::keyboard::key - direction key, int - rotation scalar
Returns: None
Author : Daniel Kilfoyle
**************************************************************************/
void cPlayer::rotateCharacter(sf::Keyboard::Key _key, int _scalar)
{
	int irotationDirection;

	if (_key == leftRotateKey)
	{
		irotationDirection = -1;
	}
	else if (_key == rightRotateKey)
	{
		irotationDirection = 1;
	}
	else
		return;

	m_fcharacterRotation += irotationDirection * _scalar * 1.0f;
	//m_characterSprite->setRotation(m_fcharacterRotation);
	m_fradiansRotation = DegreesToRadians(m_fcharacterRotation);

}

/*************************************************************************
Name: processInput
Description : processes input for the character, checking for if the keys pressed match the character's specific movement and cast keys
Parameters: None
Returns: None
Author : Daniel Kilfoyle
**************************************************************************/
void cPlayer::processInput()
{
	if (m_respawnTimer.getElapsedTime().asSeconds() >= 5.0f && !m_bActive)
	{
		respawnPlayer();
	}
	if (m_bActive)
	{
		m_Sounds->playIdleSound();
		
		
		
		if (sf::Keyboard::isKeyPressed(forwardMovementKey))
		{
			// Rotate the player, and then move player forward
			if (sf::Keyboard::isKeyPressed(leftRotateKey))
			{
				rotateCharacter(leftRotateKey, 3);
			}
			else if (sf::Keyboard::isKeyPressed(rightRotateKey))
			{
				rotateCharacter(rightRotateKey, 3);
			}
			movePlayer();
			m_bMoving = true;
		}
		// If the left rotate key is pressed, but not the forward movement, rotate the player slowly
		else if (sf::Keyboard::isKeyPressed(leftRotateKey))
		{
			rotateCharacter(leftRotateKey, 1);
			m_bMoving = false;
		}
		// If the right rotate key is pressed, but not the forward movement, rotate the player slowly
		else if (sf::Keyboard::isKeyPressed(rightRotateKey))
		{
			rotateCharacter(rightRotateKey, 1);
			m_bMoving = false;
		} else m_bMoving = false;

		// Separate if check from the movement. Process the input of casting spell after making the player move.
		if (sf::Keyboard::isKeyPressed(castSpellKey))
		{
			// Cast the spell
			castSpell();
		}
	}
	
}

/*************************************************************************
Name: movePlayer
Description : calculates movement direction based on rotation and adds to the player's current position
Parameters: None
Returns: None
Author : Daniel Kilfoyle
**************************************************************************/
void cPlayer::movePlayer()
{
	sf::Vector2f NewPos(SPEED_SCALAR * sin(m_fradiansRotation), SPEED_SCALAR * -cos(m_fradiansRotation));
	setPosition(getPosition() + NewPos);
	checkScreenWrap(level);

}



/*************************************************************************
Name: castSpell
Description : casts the player spell. Creating a projectile and adding it to the vector of active projectiles
Parameters: None
Returns: None
Author : Daniel Kilfoyle
**************************************************************************/
void cPlayer::castSpell()
{
	if (m_castTimer.getElapsedTime().asSeconds() >= m_fFireRate)
	{
		if (!m_bFired)
		{


			if (m_currentWandRef != nullptr)
			{
				m_Sounds->playFireSound();
				m_currentWandRef->castSpell( getPosition(), getRotation(), m_projectileSprite, m_projectilesList);
			}
			else 
			{
				m_Sounds->playFireSound();
				// Base projectile function. 
				cProjectile* newProjectile = new cProjectile(m_projectileSprite, getPosition(), getRotation(), false);
				m_projectilesList->push_back(newProjectile);
			}


			m_castTimer.restart();
			m_bFired = true;
		}
		else if (m_castTimer.getElapsedTime().asSeconds() >= m_fFireRate && m_bFired)
		{
			m_bFired = false;
		}
	}
	
}

void cPlayer::playerUpdate(float _deltaTime)
{
	//Any Over-Time Effects here
	if (m_InvincibilityTimer > 0)
	{
		m_InvincibilityTimer -=_deltaTime;
	}

	if (sf::Keyboard::isKeyPressed(leftRotateKey))
	{
		m_iCurrentFrame = 1;
	}
	else if (sf::Keyboard::isKeyPressed(rightRotateKey))
	{
		m_iCurrentFrame = 2;
	}
	else
	{
		m_iCurrentFrame = 0;
	}

	handleHurt(_deltaTime);
}

/*************************************************************************
Name: setProjectileSprite
Description : sets the sprite used for the player projectile 
Parameters: sf::sprite* - projectileSprite
Returns: None
Author : Daniel Kilfoyle
**************************************************************************/
void cPlayer::setProjectileSprite(sf::Sprite* _projectile)
{
	m_projectileSprite = *_projectile;
}
/*************************************************************************
Name: setProjectileList
Description : sets the reference to the projectile list 
Parameters: vector<cProjectile*>* - projectileList
Returns: None
Author : Daniel Kilfoyle
**************************************************************************/
void cPlayer::setProjectileList(std::vector<cProjectile*>* _projectiles)
{
	m_projectilesList = _projectiles;
}

void cPlayer::healthCheck()
{
	// Check if the character health has gone above its maximum, and set the value to the maximum instead.
	if (m_fcurrentHealth > m_fmaxHealth)
	{
		m_fcurrentHealth = m_fmaxHealth;
	}

	// Check if health has reached or gone below 0, then call appropriate death function for the 
	else if (m_fcurrentHealth <= 0)
	{
		m_Sounds->playDeathSound();
		m_fcurrentHealth = 0;
		// run death functions
		m_bActive = false;
		m_previousPosition = m_characterPosition;
		setPosition(sf::Vector2f(getPlayerOneOrTwo() * - 10000, -10000));
		std::cout << m_playerName << " has died." << std::endl;
		m_respawnTimer.restart();
	}

	// Return in all other cases, when health is in the intended range (Above 0 and less than or equal to maximum)
	else
		return;
}

void cPlayer::respawnPlayer()
{
	m_fcurrentHealth = m_fmaxHealth;
	m_bActive = true;
	sf::Vector2f RespawnPos = m_otherPlayer->getPosition();
	RespawnPos.x = RespawnPos.x - 100;
	setPosition(RespawnPos);	
	m_InvincibilityTimer = 5.0f;
}

void cPlayer::setWandRef(cWand* _wand) {
	m_currentWandRef = _wand;
	if (_wand != nullptr) {
		currentWandName = _wand->getName(); // Make sure your wand class has a getName() method
		_wand->applyEffect(this); // Apply any effects the wand may have
	}
	else {
		currentWandName = "Default Wand"; // Reset to default if no wand is equipped
	}
}

std::string cPlayer::getCurrentWandName() const
{
	return currentWandName;
}

void cPlayer::setCurrentWand(const std::string& wandName)
{
	currentWandName = wandName;
}


int cPlayer::getPlayerOneOrTwo()
{
	if (m_playerName == "Player 1")
	{
		return 1;
	}
	else if (m_playerName == "Player 2")
	{
		return 2;
	}
	return 0;
}


void cPlayer::setSoundManager(cSoundManager* _Sounds)
{
	m_Sounds = _Sounds;
}

void cPlayer::setOtherPlayerRef(cPlayer* _otherPlayer)
{
	m_otherPlayer = _otherPlayer;
}








void cPlayer::setProjectileCount(int _count) {
	m_iProjectileCount = _count;
}

void cPlayer::setFireRate(float _rate) {
	m_fFireRate = _rate;
}

void cPlayer::setDamageStrength(float _damage) {
	m_fDamage = _damage;
}


#include "cPlayer.h"
#include "SFML/Graphics.hpp"

cPlayer::cPlayer(sf::Sprite* _sprite, std::string _playerName, sf::Vector2f _position)
	: cCharacter(_sprite, _position)
{
	m_playerName = _playerName;

	if (m_playerName == "Player 1")
	{
		leftRotateKey = sf::Keyboard::Key::A;
		rightRotateKey = sf::Keyboard::Key::D;
		forwardMovementKey = sf::Keyboard::Key::W;
		castSpellKey = sf::Keyboard::Key::S;
	}
	else if (m_playerName == "Player 2")
	{
		leftRotateKey = sf::Keyboard::Key::Left;
		rightRotateKey = sf::Keyboard::Key::Right;
		forwardMovementKey = sf::Keyboard::Key::Up;
		castSpellKey = sf::Keyboard::Key::Down;
	}

	// Setting the current health of a player to max, as they have yet to take damage
	m_fcurrentHealth = m_fmaxHealth;
}

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
	m_characterSprite->setRotation(m_fcharacterRotation);
	m_fradiansRotation = DegreesToRadians(m_fcharacterRotation);

}
void cPlayer::processInput()
{
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
	}
	// If the left rotate key is pressed, but not the forward movement, rotate the player slowly
	else if (sf::Keyboard::isKeyPressed(leftRotateKey))
	{
		rotateCharacter(leftRotateKey, 1);
	}
	// If the right rotate key is pressed, but not the forward movement, rotate the player slowly
	else if (sf::Keyboard::isKeyPressed(rightRotateKey))
	{
		rotateCharacter(rightRotateKey, 1);
	}

	// Separate if check from the movement. Process the input of casting spell after making the player move.
	if (sf::Keyboard::isKeyPressed(castSpellKey))
	{
		// Cast the spell
	}
}

void cPlayer::movePlayer()
{
	std::cout << m_playerName << " position: " << m_characterSprite->getPosition().x << " , " << m_characterSprite->getPosition().y << std::endl;
	//m_characterSprite->move
	sf::Vector2f NewPos(SPEED_SCALAR * sin(m_fradiansRotation), SPEED_SCALAR * -cos(m_fradiansRotation));
	setPosition(getPosition() + NewPos);
	//m_playerSprite.setPosition()
	
}


void cPlayer::draw()
{
	
	m_characterSprite->setOrigin(m_characterSprite->getTexture()->getSize().x / 2, m_characterSprite->getTexture()->getSize().y / 2);

	//p_windowRef->draw(m_characterSprite);
}

void cPlayer::castSpell()
{

}



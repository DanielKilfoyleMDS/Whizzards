#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "MathLibrary.h"

class cCharacter
{
public:
	// TODO pass in sprite instead of load on character creation -  In game manager
	// TODO - Move character name to player if needed.
	cCharacter(std::string _FilePath, std::string _CharacterName, sf::Vector2f _StartPosition);

	// setHealth function used for setting health to specific numbers, instead of applying healing or damage as in update health. 
	void setHealth(float _Health);

	// Update health function, which works for positive and negative values. To be used for healing and damaging.
	void updateHealth(float _Change);

	// Virtual health check for enemies and players to use and redefine as necessary.
	// will check the character's health against its max and min, and runs necessary functions depending on the health value
	virtual void healthCheck();

	// Changed setSprite to virtual as it will be used only for the enemies
	virtual void setSprite(std::string _FilePath);

	void setWindowRef(sf::RenderWindow* _window) { p_windowRef = _window; };

	// DONE - lower upper 
	void setPosition(sf::Vector2f _Pos) { m_characterSprite.setPosition(_Pos); m_characterPosition = _Pos; }
	sf::Vector2f getPosition() { return m_characterSprite.getPosition(); };



	// DONE - Remove as convert is in the math library
	// DONE - Add set rotation
	//void convertRotation();
	void setRotation(float _Rotation);

	// DONE - Make virtual or move into child classes as needed
	virtual void moveCharacter();

	// DONE - Lower upper. 
	// DONE - return pointer instead of value
	sf::Sprite* getSprite();

protected:

	// maxHealth and currentHealth  of characters, will be overriden by child classes, so was not set to const. 
	float m_fmaxHealth;
	float m_fcurrentHealth;


	// Constant variables. These will not change. Therefore, have been made as const. 
	const float MAX_SPEED = 50.0f;
	const float SPEED_SCALAR = 10.0f;
		

	sf::RenderWindow* p_windowRef;

	sf::Sprite m_characterSprite;
	sf::Sprite* p_Sprite;
	sf::Texture m_characterTexture;

	sf::Vector2f m_characterPosition;
	
	// rotation values used for rotating the sprite
	float m_fcharacterRotation;
	// radians rotations to be used for moving, as c++ trigonometry functions use radians instead of degrees
	float m_fradiansRotation;
	
};


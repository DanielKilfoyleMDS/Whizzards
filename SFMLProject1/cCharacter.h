/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : cCharacter.h
Description : Base character class. Is the parent class for enemies and players. Contains all methods that are needed by both child classes
Author : Daniel Kilfoyle & Jayden Burns
Mail : DanielKilfoyle@mds.ac.nz & JaydenBurns@mds.ac.nz
**************************************************************************/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "cLevel.h"
#include "MathLibrary.h"

enum CharacterType
{
	Player,
	Enemy
};

class cCharacter
{
public:
	cCharacter(sf::Sprite* _sprite, sf::Vector2f _StartPosition);

	// setHealth function used for setting health to specific numbers, instead of applying healing or damage as in update health. 
	void setHealth(float _Health);
	float getHealth();

	float getMaxHealth();

	// Update health function, which works for positive and negative values. To be used for healing and damaging.
	void updateHealth(float _Change);

	// Virtual health check for enemies and players to use and redefine as necessary.
	// will check the character's health against its max and min, and runs necessary functions depending on the health value
	virtual void healthCheck();

	virtual void setPosition(sf::Vector2f _Pos) { m_characterPosition = _Pos;}
	virtual sf::Vector2f getPosition() { return m_characterPosition; };


	// Set and get for the character's type
	void setCharacterType(CharacterType _type);
	CharacterType getCharacterType();

	void setRotation(float _Rotation);
	float getRotation();

	// DONE - Make virtual or move into child classes as needed
	virtual void moveCharacter();


	int framesPassed(float _deltaTime);
	int getFrame();
	void setFrame(int _Frame);

	sf::Vector2f getHitbox() { return m_hitboxSize; };
	
	bool applyDamage(float _Damage);
	void handleHurt(float deltaTime);

	void checkScreenWrap(class cLevel _Level);



	bool isInvincible();


protected:

	// maxHealth and currentHealth  of characters, will be overriden by child classes, so was not set to const. 
	float m_fmaxHealth;
	float m_fcurrentHealth;


	// Constant variables. These will not change. Therefore, have been made as const. 
	const float MAX_SPEED = 50.0f;
	const float SPEED_SCALAR = 5.0f;
		
	CharacterType m_characterType;

	//HurtCode
	float m_fHurtTime = 0.0f;
	float m_fHurtMaxTime = 0.5f;

	//Animation Code
	int m_iCurrentFrame = 0.0f;
	float m_fAnimationTime = 0.0f;
	float m_fSecondsPerFrame = 1.0f;

	sf::Texture m_characterTexture;

	sf::Vector2f m_characterPosition;
	
	// rotation values used for rotating the sprite
	float m_fcharacterRotation;
	// radians rotations to be used for moving, as c++ trigonometry functions use radians instead of degrees
	float m_fradiansRotation;

	sf::Vector2f m_hitboxSize;
	

	//LevelWrap
	float m_maxXPos;
	float m_minXPos;
	float m_maxYPos;
	float m_minYPos;

	

	float m_InvincibilityTimer = 0.0f;

	
};


/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : cProjectile.h
Description : Projectile class to interact with characters in game
Author : Daniel Kilfoyle
Mail : DanielKilfoyle@mds.ac.nz
**************************************************************************/

#pragma once
#include "SFML/Graphics.hpp"
#include "MathLibrary.h"

class cProjectile
{
public:
	cProjectile(sf::Sprite _sprite, sf::Vector2f _pos, float _rotation, bool _enemy);
	void tick(float _deltaTime);
	void setDamage(float _damage);
	float getDamage();
	

	float getRotation();
	sf::Vector2f getPosition();
	bool getOwned();

	int framesPassed(float _deltaTime);
	int getFrame();
	void setFrame(int _Frame);

private:
	sf::Vector2f m_position;

	float m_fRotation;

	sf::Vector2f m_velocity;

	bool b_enemyOwned;

	float m_fDamage = -1;

	//Animation Code
	int m_iCurrentFrame = 0.0f;
	float m_fAnimationTime = 0.0f;
	float m_fSecondsPerFrame = 0.4f;
};


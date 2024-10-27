/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : cProjectile.cpp
Description : Projectile class to interact with characters in game
Author : Daniel Kilfoyle
Mail : DanielKilfoyle@mds.ac.nz
**************************************************************************/

#include "cProjectile.h"

/*************************************************************************
Name: cProjectile
Description : constructor for the projectile 
Parameters: sf::sprite - sprite, sf::vector2f - start position, float - rotation, bool - owned by enemy
Returns: None
Author : Daniel Kilfoyle
**************************************************************************/
cProjectile::cProjectile(sf::Sprite _sprite, sf::Vector2f _pos, float _rotation, bool _enemy)
{

	m_position = _pos;

	
	m_velocity.x = 10.0f * sin(DegreesToRadians(_rotation));
	m_velocity.y = 10.0f * -cos(DegreesToRadians(_rotation));

	b_enemyOwned = _enemy;


	m_hitboxSize.x = _sprite.getTexture()->getSize().x;
	m_hitboxSize.y = _sprite.getTexture()->getSize().y;

}


/*************************************************************************
Name: tick
Description : tick function for moving the projectile when tick is called
Parameters: None
Returns: None
Author : Daniel Kilfoyle
**************************************************************************/
void cProjectile::tick(float _deltaTime)
{
	m_position += m_velocity;
	//TO DO - Rotation

	setFrame(getFrame() + framesPassed(_deltaTime));
	if (m_iCurrentFrame > 4)
	{
		m_iCurrentFrame = 0;
	}

}

void cProjectile::setDamage(float _damage)
{
	m_fDamage = _damage;
}

float cProjectile::getDamage()
{
	return m_fDamage;
}

float cProjectile::getRotation()
{
	return m_fRotation;
}

sf::Vector2f cProjectile::getPosition()
{
	return m_position;
}

bool cProjectile::getOwned()
{
	return b_enemyOwned;
}

/*************************************************************************
Name: framesPassed
Description : returns how many frames have passed due to deltaTime
Parameters: float _deltaTime
Returns: int Frames Passed
Author : Jayden Burns
**************************************************************************/
int cProjectile::framesPassed(float _deltaTime)
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

int cProjectile::getFrame()
{
	return m_iCurrentFrame;
}

void cProjectile::setFrame(int _Frame)
{
	m_iCurrentFrame = _Frame;
}

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
	m_sprite = _sprite;
	m_sprite.setOrigin(_sprite.getTexture()->getSize().x / 2, _sprite.getTexture()->getSize().y / 2);

	m_position = _pos;

	m_sprite.setPosition(_pos);

	m_sprite.setRotation(_rotation);
	
	m_velocity.x = 10.0f * sin(DegreesToRadians(_rotation));
	m_velocity.y = 10.0f * -cos(DegreesToRadians(_rotation));

	b_enemyOwned = _enemy;

}

/*************************************************************************
Name: tick
Description : tick function for moving the projectile when tick is called
Parameters: None
Returns: None
Author : Daniel Kilfoyle
**************************************************************************/
void cProjectile::tick()
{
	m_sprite.move(m_velocity);
}

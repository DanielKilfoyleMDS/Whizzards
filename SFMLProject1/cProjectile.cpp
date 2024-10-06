#include "cProjectile.h"

cProjectile::cProjectile(sf::Sprite _sprite, sf::Vector2f _pos, float _rotation)
{
	m_Sprite = _sprite;

	m_Position = _pos;

	m_Sprite.setPosition(_pos);

	m_Sprite.setRotation(_rotation);
	
	m_velocity.x = 10.0f * sin(DegreesToRadians(_rotation));
	m_velocity.y = 10.0f * -cos(DegreesToRadians(_rotation));
}

void cProjectile::tick()
{
	m_Sprite.move(m_velocity);
}

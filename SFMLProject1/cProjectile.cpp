#include "cProjectile.h"

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


void cProjectile::tick()
{
	m_sprite.move(m_velocity);
}

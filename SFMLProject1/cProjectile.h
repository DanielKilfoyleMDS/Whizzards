#pragma once
#include "SFML/Graphics.hpp"
#include "MathLibrary.h"

class cProjectile
{
public:
	cProjectile(sf::Sprite _sprite, sf::Vector2f _pos, float _rotation, bool _enemy);


	sf::Sprite m_sprite;
	sf::Vector2f m_position;

	float m_fRotation;

	sf::Vector2f m_velocity;

	bool b_enemyOwned;

	void tick();


	
private:

};


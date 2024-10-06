#pragma once
#include "SFML/Graphics.hpp"
#include "MathLibrary.h"

class cProjectile
{
public:
	cProjectile(sf::Sprite _sprite, sf::Vector2f _pos, float _rotation);


	sf::Sprite m_Sprite;
	sf::Vector2f m_Position;

	float m_fRotation;

	sf::Vector2f m_velocity;

	void tick();
	
private:

};


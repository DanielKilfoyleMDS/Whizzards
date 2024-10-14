#include "cWandPickup.h"

cWandPickup::cWandPickup(cWand* _wand, sf::Vector2f _position, sf::Sprite* _Sprite)
{
	m_wand = _wand;
	m_position = _position;
	m_wandSprite = _Sprite;
	std::cout << "WandPickupSpawned" << std::endl;
}

cWandPickup::~cWandPickup()
{
}

sf::Sprite* cWandPickup::getSprite()
{
	return m_wandSprite;
}

cWand* cWandPickup::getWand()
{
	return m_wand;
}

sf::Vector2f cWandPickup::getPosition()
{
	return m_position;
}

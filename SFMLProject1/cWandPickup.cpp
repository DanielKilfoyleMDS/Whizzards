#include "cWandPickup.h"
#include "cPlayer.h"

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

bool cWandPickup::getPickedUp()
{
	return m_bpickedup;
}

void cWandPickup::playerCollision(cPlayer* _other)
{
	//set wand here

	//WandManager checks this to remove/destroy this
	m_bpickedup = true;
}


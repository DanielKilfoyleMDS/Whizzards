#pragma once
#include "cWand.h"

class cWandPickup
{
public:
	cWandPickup(cWand* _wand, sf::Vector2f _position, sf::Sprite* _Sprite);
	~cWandPickup();

	sf::Sprite* getSprite();
	cWand* getWand();
	sf::Vector2f getPosition();

private:
	cWand* m_wand = nullptr;
	sf::Vector2f m_position;
	sf::Sprite* m_wandSprite;
};


#pragma once
#include "cWand.h"
class cRapidWand : public cWand
{
public:
	cRapidWand();
	~cRapidWand();

	void applyEffect(cPlayer* _player) override;

	void castSpell(sf::Vector2f _PlayerPos, float _playerRot, sf::Sprite _projSprite, std::vector<cProjectile*>* _ProjList) override;

	void draw(sf::RenderWindow& window) override {
		// Implement the draw function
		window.draw(wandSprite);
	}
};


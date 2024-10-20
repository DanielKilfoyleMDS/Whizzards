#pragma once
#include "cWand.h"

class cWandPickup
{
public:
	cWandPickup(cWand* _wand, sf::Vector2f _position, sf::Sprite* _Sprite);
	~cWandPickup();

	cWand* getWand();
	sf::Vector2f getPosition();
	bool getPickedUp();

	void playerCollision(class cPlayer* _other);

	void update(float _deltaTime);

	int framesPassed(float _deltaTime);
	int getFrame();
	void setFrame(int _Frame);

private:

	bool m_bpickedup = false;

	cWand* m_wand = nullptr;
	sf::Vector2f m_position;

	//Animation Code
	int m_iCurrentFrame = 0.0f;
	float m_fAnimationTime = 0.0f;
	float m_fSecondsPerFrame = 1.0f;
};


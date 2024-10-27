#include "cWandPickup.h"
#include "cPlayer.h"

cWandPickup::cWandPickup(cWand* _wand, sf::Vector2f _position, sf::Sprite* _Sprite)
{
	m_wand = _wand;
	m_position = _position;

	m_hitboxSize.x = _Sprite->getTexture()->getSize().x;
	m_hitboxSize.y = _Sprite->getTexture()->getSize().y;
}

cWandPickup::~cWandPickup()
{
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
	_other->setWandRef(m_wand);
	//WandManager checks this to remove/destroy this
	m_bpickedup = true;
}

void cWandPickup::update(float _deltaTime)
{
	//AnimCode, delete OverTime;


}

/*************************************************************************
Name: framesPassed
Description : returns how many frames have passed due to deltaTime
Parameters: float _deltaTime
Returns: int Frames Passed
Author : Jayden Burns
**************************************************************************/
int cWandPickup::framesPassed(float _deltaTime)
{
	int FramesPassed = 0;
	m_fAnimationTime += _deltaTime;
	while (m_fAnimationTime > m_fSecondsPerFrame)
	{
		m_fAnimationTime -= 1;
		FramesPassed++;
	}
	return FramesPassed;
}

int cWandPickup::getFrame()
{
	return m_iCurrentFrame;
}

void cWandPickup::setFrame(int _Frame)
{
	m_iCurrentFrame = _Frame;
}

/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : cGameCameras.cpp
Description : Handles Cameras and views for Whizzards Game
Author : Jayden Burns
Mail : JaydenBurns@mds.ac.nz
**************************************************************************/
#include "cGameCameras.h"
#include <iostream>
#include "cCharacter.h"
#include "cProjectile.h"
#include "MathLibrary.h"
#include "cWandPickup.h"

/************************************************************************
Name: cGameCameras
Description : Constructs Cameras
Parameters: sf::RenderWindow* _window, int _levelXSize, int _levelYSize
Returns: None
Author : Jayden Burns
**************************************************************************/
cGameCameras::cGameCameras(sf::RenderWindow* _window, int _levelXSize, int _levelYSize)
{
	m_iWindowHeight = (int)_window->getSize().y;
	m_iWindowWidth = (int)_window->getSize().x;

	//TODO - Unhardcode these values
	m_LevelCenter = sf::Vector2f((48 * 64) / 2, (47 * 64) / 2);
	m_iMapXSize = (48 * 64);
	m_iMapYSize = (47 * 64);
	
	m_firstPlayerView = new sf::View(sf::Vector2f(m_iWindowWidth/2, m_iWindowHeight), sf::Vector2f(m_iWindowWidth/4, m_iWindowHeight/2));
	m_secondPlayerView = new sf::View(sf::Vector2f(m_iWindowWidth/2, m_iWindowHeight), sf::Vector2f(m_iWindowWidth/4, m_iWindowHeight/2));
	m_playerCombinedView = new sf::View(sf::Vector2f(m_iWindowWidth, m_iWindowHeight), sf::Vector2f(m_iWindowWidth / 2, m_iWindowHeight / 2));
	
	
	//Double The size
	m_firstPlayerView->setSize(m_iWindowWidth,m_iWindowHeight * 2);
	m_secondPlayerView->setSize(m_iWindowWidth,m_iWindowHeight * 2);
	m_playerCombinedView->setSize(m_iWindowWidth * 2,m_iWindowHeight * 2);
	m_fcameraJoinDistance = 600;

	m_windowRef = _window;
	m_firstPlayerView->setViewport(sf::FloatRect(0.0f, 0.0f, 0.5f, 1.0f)); //Looks wonky due to scaling
    m_secondPlayerView->setViewport(sf::FloatRect(0.5f, 0.0f, 0.5f, 1.0f));
	m_playerCameraRelativeVector = sf::Vector2f(0, 0);

	

}

/*************************************************************************
Name: ~cGameCameras
Description : Deconstructs Cameras
Parameters: None
Returns: None
Author : Jayden Burns
**************************************************************************/
cGameCameras::~cGameCameras()
{
	delete m_firstPlayerView;
	m_firstPlayerView = nullptr;
	delete m_secondPlayerView;
	m_secondPlayerView = nullptr;
	delete m_playerCombinedView;
	m_playerCombinedView = nullptr;
	m_windowRef = nullptr; //Window is not owned by Camera so is not Deleted;

}

/*************************************************************************
Name: setViewFirstPlayer
Description : Sets SFML to render to first player view
Parameters: None
Returns: None
Author : Jayden Burns
**************************************************************************/
void cGameCameras::setViewFirstPlayer()
{
	m_windowRef->setView(*m_firstPlayerView);
}

/*************************************************************************
Name: setViewFirstPlayer
Description : Sets SFML to render to Second player view
Parameters: None
Returns: None
Author : Jayden Burns
**************************************************************************/
void cGameCameras::setViewSecondPlayer()
{
	m_windowRef->setView(*m_secondPlayerView);
}

/*************************************************************************
Name: UpdatePositions
Description : Updates Positions of Splitscreen Cameras
Parameters: sf::Vector2f _cameraOnePosition, sf::Vector2f _cameraTwoPosition
Returns: None
Author : Jayden Burns
**************************************************************************/
void cGameCameras::UpdatePositions(sf::Vector2f _cameraOnePosition, sf::Vector2f _cameraTwoPosition)
{
	//Smoothing Should be applied here!
	m_firstPlayerView->setCenter(RestrictCameraToBounds(_cameraOnePosition, true));
	m_secondPlayerView->setCenter(RestrictCameraToBounds(_cameraTwoPosition, true));
	UpdateCameraRelative(_cameraOnePosition, _cameraTwoPosition);
}

/*************************************************************************
Name: UseCombinedView
Description : Checks to see if cameras are close enough to merge
Parameters: None
Returns: Bool
Author : Jayden Burns
**************************************************************************/
bool cGameCameras::UseCombinedView()
{
	return m_fcameraCurrentDistance < m_fcameraJoinDistance;
}

/*************************************************************************
Name: SetViewBothPlayers
Description : Sets SFML to render to unsplit player view
Parameters: None
Returns: None
Author : Jayden Burns
**************************************************************************/
void cGameCameras::SetViewBothPlayers()
{
	m_playerCombinedView->setCenter(m_secondPlayerView->getCenter() + Normalize(m_playerCameraRelativeVector) * (m_fcameraCurrentDistance/2));

	m_windowRef->setView(*m_playerCombinedView);
}

/*************************************************************************
Name: Render
Description : Renders cCharacter to current view
Parameters: cCharacter* _Character, sf::RenderWindow* _window
Returns: None
Author : Jayden Burns
**************************************************************************/
void cGameCameras::Render(cCharacter* _Character, sf::RenderWindow* _window)
{
	sf::Sprite* RenderSprite = _Character->getSprite();
	RenderSprite->setPosition(_Character->getPosition());
	RenderSprite->setRotation(_Character->getRotation());
	_window->draw(*RenderSprite);
}

/*************************************************************************
Name: Render
Description : Renders cProjectile to current view
Parameters: cProjectile* _Projectile, sf::RenderWindow* _window
Returns: None
Author : Jayden Burns
**************************************************************************/
void cGameCameras::Render(cProjectile* _Projectile, sf::RenderWindow* _window)
{
	sf::Sprite* RenderSprite = _Projectile->getSprite(); //TODO - Getter
	RenderSprite->setPosition(_Projectile->getPosition());
	RenderSprite->setRotation(_Projectile->getRotation());
	_window->draw(*RenderSprite);
}

/*************************************************************************
Name: Render
Description : Renders sf::Sprite to current view
Parameters: sf::Sprite* _Sprite, sf::RenderWindow* _window
Returns: None
Author : Jayden Burns
**************************************************************************/
void cGameCameras::Render(sf::Sprite* _Sprite, sf::RenderWindow* _window)
{
	_window->draw(*_Sprite);
}

/*************************************************************************
Name: Render
Description : Renders wandpickup to current view
Parameters: cWandPickup* _WandDrop, sf::RenderWindow* _window
Returns: None
Author : Jayden Burns
**************************************************************************/
void cGameCameras::Render(cWandPickup* _WandDrop, sf::RenderWindow* _window)
{
	sf::Sprite* RenderSprite = _WandDrop->getSprite();
	RenderSprite->setPosition(_WandDrop->getPosition());
	_window->draw(*RenderSprite);
}

/*************************************************************************
Name: UpdateCameraRelative
Description : Updates Position of Unsplit camera relative to player distance
Parameters: sf::Vector2f _playerOnePosition, sf::Vector2f _playerTwoPosition
Returns: None
Author : Jayden Burns
**************************************************************************/
void cGameCameras::UpdateCameraRelative(sf::Vector2f _playerOnePosition, sf::Vector2f _playerTwoPosition)
{
	m_playerCameraRelativeVector = (_playerOnePosition - _playerTwoPosition);
	m_fcameraCurrentDistance = VectorLength(m_playerCameraRelativeVector);
	m_playerCombinedView->setCenter(RestrictCameraToBounds(m_playerCombinedView->getCenter(), false));
}

/*************************************************************************
Name: RestrictCameraToBounds
Description : Updates Position of camera to stay within game bounds
Parameters: sf::Vector2f _cameraPosition, bool _bSplit
Returns: sf::Vector2f - new position
Author : Jayden Burns
**************************************************************************/
sf::Vector2f cGameCameras::RestrictCameraToBounds(sf::Vector2f _cameraPosition, bool _bSplit)
{
	int XScale = 2;
	if (_bSplit)
	{
		XScale = 4;
	}
	
	//TODO - Move these to member variables to avoid doing these calculations every frame
	float RightLimit = m_LevelCenter.x + m_iMapXSize / 2;
	float LeftLimit = m_LevelCenter.x + -m_iMapXSize / 2;
	float BottomLimit = m_LevelCenter.y + m_iMapYSize / 2;
	float TopLimit = m_LevelCenter.y + -m_iMapYSize / 2;

	int NewPositionX = _cameraPosition.x;
	int NewPositionY = _cameraPosition.y;
	//Right and Left Side of Screen
	if (_cameraPosition.x + m_iWindowWidth / XScale >= RightLimit)
	{
		NewPositionX = RightLimit - m_iWindowWidth / 4;
	}
	else if (_cameraPosition.x - m_iWindowWidth / XScale < LeftLimit)
	{
		NewPositionX = LeftLimit + m_iWindowWidth / 4; //LEFT
	}

	//Bottom and Top Side of Screen
	if (_cameraPosition.y + m_iWindowHeight / 2 >= BottomLimit)
	{
		NewPositionY = BottomLimit - m_iWindowHeight / 2;
	}
	else if (_cameraPosition.y - m_iWindowHeight / 2 < TopLimit)
	{
		NewPositionY = TopLimit + m_iWindowHeight / 2; //TOP
	}

	return sf::Vector2f(NewPositionX,NewPositionY);
}

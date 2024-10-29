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
#include "cEnemy.h"
#include "cPlayer.h"
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
cGameCameras::cGameCameras(sf::RenderWindow* _window, int _levelXSize, int _levelYSize, cGameManager* _GameManager)
{
	m_iWindowHeight = (int)_window->getSize().y;
	m_iWindowWidth = (int)_window->getSize().x;

	//TODO - Unhardcode these values
	m_LevelCenter = sf::Vector2f((48 * 64) / 2, (47 * 64) / 2);
	m_iMapXSize = (48 * 64);
	m_iMapYSize = (47 * 64);
	
	m_leftSideView = new sf::View(sf::Vector2f(m_iWindowWidth/2, m_iWindowHeight), sf::Vector2f(m_iWindowWidth/4, m_iWindowHeight/2));
	m_rightSideView = new sf::View(sf::Vector2f(m_iWindowWidth/2, m_iWindowHeight), sf::Vector2f(m_iWindowWidth/4, m_iWindowHeight/2));
	m_playerCombinedView = new sf::View(sf::Vector2f(m_iWindowWidth, m_iWindowHeight), sf::Vector2f(m_iWindowWidth / 2, m_iWindowHeight / 2));
	
	
	//Double The size
	m_leftSideView->setSize(m_iWindowWidth/1.5,(m_iWindowHeight * 2)/1.5);
	m_rightSideView->setSize(m_iWindowWidth / 1.5, (m_iWindowHeight * 2) / 1.5);
	m_playerCombinedView->setSize((m_iWindowWidth * 2)/1.5,(m_iWindowHeight * 2)/1.5);
	m_fcameraJoinDistance = 600;

	m_windowRef = _window;
	m_leftSideView->setViewport(sf::FloatRect(0.0f, 0.0f, 0.5f, 1.0f)); 
    m_rightSideView->setViewport(sf::FloatRect(0.5f, 0.0f, 0.5f, 1.0f));
	m_playerCameraRelativeVector = sf::Vector2f(0, 0);

	m_currentGameManager = _GameManager;

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
	delete m_leftSideView;
	m_leftSideView = nullptr;
	delete m_rightSideView;
	m_rightSideView = nullptr;
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
void cGameCameras::setViewLeftSide()
{
	m_windowRef->setView(*m_leftSideView);
}

/*************************************************************************
Name: setViewFirstPlayer
Description : Sets SFML to render to Second player view
Parameters: None
Returns: None
Author : Jayden Burns
**************************************************************************/
void cGameCameras::setViewRightSide()
{
	m_windowRef->setView(*m_rightSideView);
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
	m_leftSideView->setCenter(RestrictCameraToBounds(_cameraOnePosition, true));
	m_rightSideView->setCenter(RestrictCameraToBounds(_cameraTwoPosition, true));
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
	m_playerCombinedView->setCenter(m_rightSideView->getCenter() + Normalize(m_playerCameraRelativeVector) * (m_fcameraCurrentDistance/2));

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
	//sf::Sprite* RenderSprite = _Character->getSprite();
	//RenderSprite->setPosition(_Character->getPosition());
	//RenderSprite->setRotation(_Character->getRotation());
	//_window->draw(*RenderSprite);
}

/*************************************************************************
Name: Render
Description : Renders cEnemy to current view
Parameters: cEnemy* _Enemy, sf::RenderWindow* _window
Returns: None
Author : Jayden Burns
**************************************************************************/
void cGameCameras::Render(cEnemy* _Enemy, sf::RenderWindow* _window)
{
	sf::Sprite* RenderSprite = nullptr;

	switch (_Enemy->getEnemyType())
	{
	case Type_Asteroid:
		RenderSprite = m_currentGameManager->getEnemyAsteroidSprite();
		break;
	case Type_Random:
		RenderSprite = m_currentGameManager->getEnemyRandomSprite(_Enemy->getFrame());
		break;
	case Type_Chase:
		RenderSprite = m_currentGameManager->getEnemyChaseSprite(_Enemy->getFrame());
		break;
	case Type_Projectile:
		RenderSprite = m_currentGameManager->getEnemyDefaultSprite();
		break;
	default:
		RenderSprite = m_currentGameManager->getEnemyDefaultSprite();
		break;
	}

	if (RenderSprite != nullptr)
	{
		RenderSprite->setPosition(_Enemy->getPosition());
		RenderSprite->setRotation(_Enemy->getRotation());
		_window->draw(*RenderSprite);
	}
}

void cGameCameras::Render(cPlayer* _Player, sf::RenderWindow* _window)
{
	sf::Sprite* RenderSprite = nullptr;



	if (_Player->isInvincible()) //Replace with a currently Invincible check
	{
		sf::Sprite* Shield = m_currentGameManager->getPlayerInvincSprite();
		Shield->setPosition(_Player->getPosition());
		Shield->setRotation(_Player->getRotation());
		_window->draw(*Shield);

	}


	if (_Player->getPlayerOneOrTwo() == 1)
	{
		RenderSprite = m_currentGameManager->getFirstPlayerSprite(_Player->getFrame());
	}
	else if (_Player->getPlayerOneOrTwo() == 2)
	{
		RenderSprite = m_currentGameManager->getSecondPlayerSprite(_Player->getFrame());
	}

	if (RenderSprite != nullptr)
	{
		RenderSprite->setPosition(_Player->getPosition()); 
		RenderSprite->setRotation(_Player->getRotation());
		_window->draw(*RenderSprite);
	}
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
	sf::Sprite* RenderSprite = nullptr;

	//Pick the player.
	RenderSprite = m_currentGameManager->getFireProjectile(_Projectile->getFrame());
	
	if (RenderSprite != nullptr)
	{
		RenderSprite->setPosition(_Projectile->getPosition());
		RenderSprite->setRotation(_Projectile->getRotation());
		_window->draw(*RenderSprite);
	}
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
	sf::Sprite* RenderSprite = nullptr;

	RenderSprite = m_currentGameManager->getWandPickupSprite(_WandDrop->getFrame());

	if (RenderSprite != nullptr)
	{
		RenderSprite->setPosition(_WandDrop->getPosition());
		_window->draw(*RenderSprite);
	}
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
	//if (m_playerCameraRelativeVector.x > 0)
	//{
	//	std::cout << "P1 to the right" << std::endl;
	//}
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

void cGameCameras::renderSplitViews(cPlayer* _Player1, cPlayer* _Player2, std::vector<class cEnemy*> _activeEnemies, std::vector<cProjectile*> _Projectiles, std::vector<class cWandPickup*> _wandPickups)
{
	
	setViewLeftSide();
	renderToView(_Player1, _Player2, _activeEnemies, _Projectiles, _wandPickups);
	setViewRightSide();
	renderToView(_Player1, _Player2, _activeEnemies, _Projectiles, _wandPickups);
}

void cGameCameras::renderFullView(cPlayer* _Player1, cPlayer* _Player2, std::vector<class cEnemy*> _activeEnemies, std::vector<cProjectile*> _Projectiles, std::vector<class cWandPickup*> _wandPickups)
{
	SetViewBothPlayers();
	renderToView(_Player1, _Player2, _activeEnemies, _Projectiles, _wandPickups);
}

void cGameCameras::renderToView(cPlayer* _Player1, cPlayer* _Player2, std::vector<class cEnemy*> _activeEnemies, std::vector<cProjectile*> _Projectiles, std::vector<class cWandPickup*> _wandPickups)
{
	Render(_Player1, m_windowRef);
	Render(_Player2, m_windowRef);

	for (auto iter : _activeEnemies)
	{
		Render(iter, m_windowRef);
	}
	for (auto iter : _Projectiles)
	{
		Render(iter, m_windowRef);
	}
	for (auto& wandPickup : _wandPickups)
	{
		Render(wandPickup, m_windowRef);
	}
}
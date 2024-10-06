#include "cGameCameras.h"
#include <iostream>
#include "MathLibrary.h"

cGameCameras::cGameCameras(sf::RenderWindow* _window, int _levelXSize, int _levelYSize)
{
	m_iWindowHeight = (int)_window->getSize().y;
	m_iWindowWidth = (int)_window->getSize().x;

	m_iMapXSize = _levelXSize;
	m_iMapYSize = _levelYSize;
	
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

void cGameCameras::setViewFirstPlayer()
{
	m_windowRef->setView(*m_firstPlayerView);
}

void cGameCameras::setViewSecondPlayer()
{
	m_windowRef->setView(*m_secondPlayerView);
}



void cGameCameras::UpdatePositions(sf::Vector2f _cameraOnePosition, sf::Vector2f _cameraTwoPosition)
{
	//Smoothing Should be applied here!
	m_firstPlayerView->setCenter(RestrictCameraToBounds(_cameraOnePosition, true));
	m_secondPlayerView->setCenter(RestrictCameraToBounds(_cameraTwoPosition, true));
	UpdateCameraRelative(_cameraOnePosition, _cameraTwoPosition);
}

bool cGameCameras::UseCombinedView()
{
	return m_fcameraCurrentDistance < m_fcameraJoinDistance;
}

void cGameCameras::SetViewBothPlayers()
{
	m_playerCombinedView->setCenter(m_secondPlayerView->getCenter() + Normalize(m_playerCameraRelativeVector) * (m_fcameraCurrentDistance/2));

	m_windowRef->setView(*m_playerCombinedView);
}

void cGameCameras::UpdateCameraRelative(sf::Vector2f _playerOnePosition, sf::Vector2f _playerTwoPosition)
{
	m_playerCameraRelativeVector = (_playerOnePosition - _playerTwoPosition);
	m_fcameraCurrentDistance = VectorLength(m_playerCameraRelativeVector);
	m_playerCombinedView->setCenter(RestrictCameraToBounds(m_playerCombinedView->getCenter(), false));
}

sf::Vector2f cGameCameras::RestrictCameraToBounds(sf::Vector2f _cameraPosition, bool _bSplit)
{
	int XScale = 2;
	if (_bSplit)
	{
		XScale = 4;
	}

	int NewPositionX = _cameraPosition.x;
	int NewPositionY = _cameraPosition.y;
	if (_cameraPosition.x + m_iWindowWidth / XScale >= m_iMapXSize / 2)
	{
		NewPositionX = m_iMapXSize / 2 - m_iWindowWidth / 4;
	}
	else if (_cameraPosition.x - m_iWindowWidth / XScale < -m_iMapXSize / 2)
	{
		NewPositionX = -m_iMapXSize / 2 + m_iWindowWidth / 4;
	}

	if (_cameraPosition.y + m_iWindowWidth / 2 >= m_iMapYSize / 2)
	{
		NewPositionY = m_iMapYSize / 2 - m_iWindowWidth / 2;
	}
	else if (_cameraPosition.y - m_iWindowWidth / 2 < -m_iMapYSize / 2)
	{
		NewPositionY = -m_iMapYSize / 2 + m_iWindowWidth / 2;
	}

	return sf::Vector2f(NewPositionX,NewPositionY);
}

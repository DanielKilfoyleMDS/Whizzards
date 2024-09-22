#include "cGameCameras.h"
#include <iostream>
#include "MathLibrary.h"

cGameCameras::cGameCameras(sf::RenderWindow* Window, int _LevelXSize, int _LevelYSize)
{
	m_PlayerOneView = new sf::View(sf::Vector2f(iWindowWidth/2, iWindowHeight), sf::Vector2f(iWindowWidth/4, iWindowHeight/2));
	m_PlayerTwoView = new sf::View(sf::Vector2f(iWindowWidth/2, iWindowHeight), sf::Vector2f(iWindowWidth/4, iWindowHeight/2));
	m_PlayerCombinedView = new sf::View(sf::Vector2f(iWindowWidth, iWindowHeight), sf::Vector2f(iWindowWidth / 2, iWindowHeight / 2));
	m_WindowRef = Window;
	m_PlayerOneView->setViewport(sf::FloatRect(0.0f, 0.0f, 0.5f, 1.0f)); //Looks wonky due to scaling
    m_PlayerTwoView->setViewport(sf::FloatRect(0.5f, 0.0f, 0.5f, 1.0f));
	m_PlayerCameraRelativeVector = sf::Vector2f(0, 0);

	iWindowHeight = Window->getSize().y;
	iWindowWidth = Window->getSize().x;

	iMapXSize = _LevelXSize;
	iMapYSize = _LevelYSize;

}

cGameCameras::~cGameCameras()
{
	delete m_PlayerOneView;
	m_PlayerOneView = nullptr;
	delete m_PlayerTwoView;
	m_PlayerTwoView = nullptr;
	delete m_PlayerCombinedView;
	m_PlayerCombinedView = nullptr;
	m_WindowRef = nullptr; //Window is not owned by Camera so is not Deleted;

}

void cGameCameras::setView1()
{
	m_WindowRef->setView(*m_PlayerOneView);
}

void cGameCameras::setView2()
{
	m_WindowRef->setView(*m_PlayerTwoView);
}



void cGameCameras::UpdatePositions(sf::Vector2f _cameraOnePosition, sf::Vector2f _cameraTwoPosition)
{
	//Smooting Should be applied here!
	m_PlayerOneView->setCenter(RestrictCameraToBounds(_cameraOnePosition));
	m_PlayerTwoView->setCenter(RestrictCameraToBounds(_cameraTwoPosition));
	UpdateCameraRelative(_cameraOnePosition, _cameraTwoPosition);
}

bool cGameCameras::SetFullView()
{
	m_PlayerCombinedView->setCenter(m_PlayerTwoView->getCenter() + Normalize(m_PlayerCameraRelativeVector) * (m_fCameraJoinDistance/2));

	if (m_fCameraJoinDistance < 300)
	{
		m_WindowRef->setView(*m_PlayerCombinedView);
		return true;
	} else return false;
}

void cGameCameras::UpdateCameraRelative(sf::Vector2f P1, sf::Vector2f P2)
{
	m_PlayerCameraRelativeVector = (P1 - P2);
	m_fCameraJoinDistance = VectorLength(m_PlayerCameraRelativeVector);
}

sf::Vector2f cGameCameras::RestrictCameraToBounds(sf::Vector2f _CameraPosition)
{
	float ResultX = _CameraPosition.x;
	float ResultY = _CameraPosition.y;
	if (_CameraPosition.x + iWindowWidth / 4 >= iMapXSize / 2)
	{
		ResultX = iMapXSize / 2 - iWindowWidth / 4;
	}
	else if (_CameraPosition.x - iWindowWidth / 4 < -iMapXSize / 2)
	{
		ResultX = -iMapXSize / 2 + iWindowWidth / 4;
	}

	if (_CameraPosition.y + iWindowWidth / 2 >= iMapYSize / 2)
	{
		ResultY = iMapYSize / 2 - iWindowWidth / 2;
	}
	else if (_CameraPosition.y - iWindowWidth / 2 < -iMapYSize / 2)
	{
		ResultY = -iMapYSize / 2 + iWindowWidth / 2;
	}

	return sf::Vector2f(ResultX,ResultY);
}

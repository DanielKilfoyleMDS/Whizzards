#include "cGameCameras.h"
#include <iostream>
#include "MathLibrary.h"

cGameCameras::cGameCameras(sf::RenderWindow* Window)
{
	m_P1View = new sf::View(sf::Vector2f(WindowWidth/2, WindowHeight), sf::Vector2f(WindowWidth/4, WindowHeight/2));
	m_P2View = new sf::View(sf::Vector2f(WindowWidth/2, WindowHeight), sf::Vector2f(WindowWidth/4, WindowHeight/2));
	m_FullView = new sf::View(sf::Vector2f(WindowWidth, WindowHeight), sf::Vector2f(WindowWidth / 2, WindowHeight / 2));
	m_Window = Window;
	m_P1View->setViewport(sf::FloatRect(0.0f, 0.0f, 0.5f, 1.0f)); //Looks wonky due to scaling
    m_P2View->setViewport(sf::FloatRect(0.5f, 0.0f, 0.5f, 1.0f));
	cameraGapVector = sf::Vector2f(0, 0);
}

void cGameCameras::setView1()
{
	m_Window->setView(*m_P1View);
}

void cGameCameras::setView2()
{
	m_Window->setView(*m_P2View);
}



void cGameCameras::UpdatePositions(sf::Vector2f _P1, sf::Vector2f _P2)
{
	float Cx = _P1.x;
	float Cy = _P1.y;
	//Basically, follow player until border is reached
	if (_P1.x + WindowWidth / 4 >= MapXSize / 2)
	{
		Cx = MapXSize / 2 - WindowWidth / 4;
	}
	else if (_P1.x - WindowWidth / 4 < -MapXSize / 2)
	{
		Cx = -MapXSize / 2 + WindowWidth / 4;
	}

	if (_P1.y + WindowWidth / 2 >= MapYSize / 2)
	{
		Cy = MapYSize / 2 - WindowWidth / 2;
	}
	else if (_P1.y - WindowWidth / 2 < -MapYSize / 2)
	{
		Cy = -MapYSize / 2 + WindowWidth / 2;
	}

	m_P1View->setCenter(Cx,Cy);

	Cx = _P2.x;
	Cy = _P2.y;

	if (_P2.x + WindowWidth / 4 >= MapXSize / 2)
	{
		Cx = MapXSize / 2 - WindowWidth / 4;
	}
	else if (_P2.x - WindowWidth / 4 < -MapXSize / 2)
	{
		Cx = -MapXSize / 2 + WindowWidth / 4;
	}

	if (_P2.y + WindowWidth / 2 >= MapYSize / 2)
	{
		Cy = MapYSize / 2 - WindowWidth / 2;
	}
	else if (_P2.y - WindowWidth / 2 < -MapYSize / 2)
	{
		Cy = -MapYSize / 2 + WindowWidth / 2;
	}


	m_P2View->setCenter(Cx,Cy);
	UpdateCameraRelative(_P1, _P2);
}

bool cGameCameras::SetFullView()
{
	m_FullView->setCenter(m_P2View->getCenter() + Normalize(cameraGapVector) * (distance/2));

	if (distance < 300)
	{
		m_Window->setView(*m_FullView);
		return true;
	} else return false;
}

void cGameCameras::UpdateCameraRelative(sf::Vector2f P1, sf::Vector2f P2)
{
	cameraGapVector = (P1 - P2);
	distance = VectorLength(cameraGapVector);
	if (distance < 200)
	{
		

		//Set centre to be halfway between the players
		// Okay that was wrong
		//m_P1View->setCenter(Normalize(cameraGapVector) * (VectorLength(cameraGapVector)/2));
	}


}

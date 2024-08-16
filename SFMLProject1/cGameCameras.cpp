#include "cGameCameras.h"

cGameCameras::cGameCameras(sf::RenderWindow* Window)
{
	m_P1View = new sf::View(sf::Vector2f(WindowWidth/2, WindowHeight), sf::Vector2f(WindowWidth/4, WindowHeight/2));
	m_P2View = new sf::View(sf::Vector2f(WindowWidth/2, WindowHeight), sf::Vector2f(WindowWidth/4, WindowHeight/2));
	m_Window = Window;
	m_P1View->setViewport(sf::FloatRect(0.0f, 0.0f, 0.5f, 1.0f)); //Looks wonky due to scaling
    m_P2View->setViewport(sf::FloatRect(0.5f, 0.0f, 0.5f, 1.0f));

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
	m_P1View->setCenter(_P1);
	m_P2View->setCenter(_P2);
}

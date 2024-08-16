#pragma once
#include "SFML/Graphics.hpp"
class cGameCameras
{
public:

	cGameCameras(sf::RenderWindow* Window);

	void setView1();
	void setView2();

	void UpdatePositions(sf::Vector2f _P1, sf::Vector2f _P2);

private:
	sf::View* m_P1View;
	sf::View* m_P2View;
	sf::RenderWindow* m_Window;

	const int WindowHeight = 720;
	const int WindowWidth = 1280;

	

};


//sf::View P1View(sf::Vector2f(640.f, 360.f), sf::Vector2f(1280.f, 720.f));
//sf::View P2View(sf::Vector2f(350.f, 300.f), sf::Vector2f(300.f, 200.f));
////Reset function, SetCentre, Set Size
////Move moves it, set center moves it to the location
//P1View.setViewport(sf::FloatRect(0.0f, 0.0f, 0.5f, 1.0f)); //Looks wonky due to scaling
//P2View.setViewport(sf::FloatRect(0.5f, 0.5f, 0.5f, 1.0f));
////view.setSize(1200.f, 800.f); would be a better way
////P1View.rotate(20.f);
//
//window.setView(P1View);
//window.setView(P2View);
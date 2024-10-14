/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : cGameCameras.h
Description : Handles Cameras and views for Whizzards Game
Author : Jayden Burns
Mail : JaydenBurns@mds.ac.nz
**************************************************************************/
#pragma once
#include "SFML/Graphics.hpp"
class cGameCameras
{
public:

	cGameCameras(sf::RenderWindow* _window, int _levelXSize, int _levelYSize);
	~cGameCameras();

	//TODO consistent capitalize, change from number to be more clear
	void setViewFirstPlayer();
	void setViewSecondPlayer();

	void UpdatePositions(sf::Vector2f _cameraOnePosition, sf::Vector2f _cameraTwoPosition);

	bool UseCombinedView();

	void SetViewBothPlayers();

	void Render(class cCharacter* _Character, sf::RenderWindow* _window);
	void Render(class cProjectile* _Projectile, sf::RenderWindow* _window);
	void Render(sf::Sprite* _Sprite, sf::RenderWindow* _window);
	void Render(class cWandPickup* _WandDrop, sf::RenderWindow* _window);

	//TODO Add Line for Clarity

private:
	sf::View* m_firstPlayerView;
	sf::View* m_secondPlayerView;
	sf::View* m_playerCombinedView;

	sf::RenderWindow* m_windowRef;

	//TODO - m_, Set via constructor
	int m_iWindowHeight;
	int m_iWindowWidth;
	int m_iMapXSize;
	int m_iMapYSize;


	sf::Vector2f m_LevelCenter;

	sf::Vector2f m_playerCameraRelativeVector;
	float m_fcameraCurrentDistance = 0;
	float m_fcameraJoinDistance = 300;

	void UpdateCameraRelative(sf::Vector2f _position1, sf::Vector2f _position2);
	sf::Vector2f RestrictCameraToBounds(sf::Vector2f _cameraPosition, bool _bSplit);
	

};


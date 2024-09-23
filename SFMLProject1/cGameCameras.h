#pragma once
#include "SFML/Graphics.hpp"
class cGameCameras
{
public:

	cGameCameras(sf::RenderWindow* Window, int _LevelXSize, int _LevelYSize);
	~cGameCameras();

	void setView1();
	void setView2();

	void UpdatePositions(sf::Vector2f _cameraOnePosition, sf::Vector2f _cameraTwoPosition);

	bool SetFullView();

private:
	sf::View* m_PlayerOneView;
	sf::View* m_PlayerTwoView;
	sf::View* m_PlayerCombinedView;

	sf::RenderWindow* m_WindowRef;


	int iWindowHeight = 720;
	int iWindowWidth = 1280;
	int iMapXSize = 3000;
	int iMapYSize = 3000;

	void UpdateCameraRelative(sf::Vector2f _Position1, sf::Vector2f _Position2);
	sf::Vector2f RestrictCameraToBounds(sf::Vector2f _CameraPosition);
	sf::Vector2f m_PlayerCameraRelativeVector;
	float m_fCameraJoinDistance = 0;
};


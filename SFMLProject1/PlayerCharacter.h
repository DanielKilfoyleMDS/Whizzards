// TODO - Redo 

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>


const double PI = 3.1415926535;

class PlayerCharacter
{
public:

	PlayerCharacter(std::string _FilePath, std::string _PlayerName);

	sf::RenderWindow* windowRef;

	// visual elements.
	sf::Sprite playerSprite;
	sf::Texture playerTexture;


	std::string playerName;


	// movement elements.
	sf::Vector2f playerPosition;
	float playerRotation;
	float radiansRotation;
	sf::Vector2f playerVelocity;
	float playerSpeedScalar = 10.0f;

	// player control scheme
	sf::Keyboard::Key leftRotateKey;
	sf::Keyboard::Key rightRotateKey;
	sf::Keyboard::Key forwardMoveKey;
	sf::Keyboard::Key castSpellKey;

	void Draw();
	void setSprite(std::string _FilePath);
	void setWindowRef(sf::RenderWindow* _window) { windowRef = _window; };

	void movePlayer();
	void rotatePlayer(sf::Keyboard::Key _Key);
	void castSpell();

	void SetPosition(sf::Vector2f _Pos) { playerSprite.setPosition(_Pos); playerPosition = _Pos; }
	sf::Vector2f getPosition() { return playerSprite.getPosition(); };


	void convertRotation();

	void processInput();
	

	
};

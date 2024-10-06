#pragma once
#include "cCharacter.h"
#include "MathLibrary.h"

class cPlayer : public cCharacter
{
public:
	cPlayer(std::string _filePath, std::string _PlayerName, sf::Vector2f _Position, sf::Sprite* _Sprite);
	
	
	void rotateCharacter(sf::Keyboard::Key _key, int _scalar);
	void processInput();
	void movePlayer();
	void draw();

	sf::Keyboard::Key leftRotateKey;
	sf::Keyboard::Key rightRotateKey;
	sf::Keyboard::Key forwardMovementKey;
	sf::Keyboard::Key castSpellKey;


private:

	// character name, used for setting different controls for player 1 and player 2
	std::string m_playerName;

	sf::Sprite* m_playerSprite;




};


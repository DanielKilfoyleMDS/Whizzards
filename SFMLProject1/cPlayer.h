#pragma once
#include "cCharacter.h"
#include "MathLibrary.h"

class cPlayer : public cCharacter
{
public:
	cPlayer(sf::Sprite* _Sprite, std::string _PlayerName, sf::Vector2f _Position, std::vector <cCharacter*> &_activeCharacters);
	
	
	void rotateCharacter(sf::Keyboard::Key _key, int _scalar);
	void processInput();
	void movePlayer();
	void draw();

	void castSpell();

	sf::Keyboard::Key leftRotateKey;
	sf::Keyboard::Key rightRotateKey;
	sf::Keyboard::Key forwardMovementKey;
	sf::Keyboard::Key castSpellKey;

	sf::FloatRect getBounds() {
		return m_characterSprite->getGlobalBounds();
	}


private:

	// character name, used for setting different controls for player 1 and player 2
	std::string m_playerName;
};


#pragma once
#include "cCharacter.h"
#include "MathLibrary.h"
#include "cProjectile.h"

class cPlayer : public cCharacter
{
public:
	cPlayer(sf::Sprite* _Sprite, std::string _PlayerName, sf::Vector2f _Position, std::vector<cCharacter*>* _activeCharacters);
	
	
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
	
	void setProjectileSprite(sf::Sprite* _projectile);
	void setProjectileList(std::vector<cProjectile*>* _projectiles);


private:

	// character name, used for setting different controls for player 1 and player 2
	std::string m_playerName;

	sf::Sprite m_projectileSprite;
	sf::Clock m_castTimer;
	bool m_bFired;
	std::vector<cProjectile*>* m_projectilesList;
};


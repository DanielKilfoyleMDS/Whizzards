#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "MathLibrary.h"

enum CharacterType {Player, Enemy};

class cCharacter
{
public:

	cCharacter(std::string _FilePath, std::string _CharacterName, sf::Vector2f _StartPosition);

	void setHealth(float _Health);
	float getHealth() { return currentHealth; };
	void takeDamage(float _Damage);
	void restoreHealth(float _Healing);
	void healthCheck();

	void setSprite(std::string _FilePath);
	void setWindowRef(sf::RenderWindow* _window) { windowRef = _window; };

	void SetPosition(sf::Vector2f _Pos) { characterSprite.setPosition(_Pos); characterPosition = _Pos; }
	sf::Vector2f getPosition() { return characterSprite.getPosition(); };

	std::string characterName;

	void rotateCharacter(int _Direction);
	void convertRotation();
	void moveCharacter();
protected:
	
	// Constant variables. These will not change. Therefore, have been made as const. 
	const float MAX_HEALTH = 100.0f;
	const float MAX_SPEED = 50.0f;
	const float SPEED_SCALAR = 10.0f;

	float currentHealth;

	sf::RenderWindow* windowRef;

	sf::Sprite characterSprite;
	sf::Texture characterTexture;

	sf::Vector2f characterPosition;
	
	float characterRotation;
	float radiansRotation;

	
};


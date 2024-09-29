#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "MathLibrary.h"

// TO DO - REMOVE. Unnecessary
enum CharacterType {Player, Enemy};

class cCharacter
{
public:
	// TODO pass in sprite instead of load on character creation -  In game manager
	// TODO - Move character name to player if needed.
	cCharacter(std::string _FilePath, std::string _CharacterName, sf::Vector2f _StartPosition);


	void setHealth(float _Health);
	float getHealth() { return currentHealth; };

	// TODO - combine into "updateHealth" takes in negative or possitive for healing / damage
	void takeDamage(float _Damage);
	void restoreHealth(float _Healing);

	// TODO - Make virtual for enemies and players to 
	void healthCheck();

	void setSprite(std::string _FilePath);
	void setWindowRef(sf::RenderWindow* _window) { windowRef = _window; };

	// TODO - lower upper 
	void SetPosition(sf::Vector2f _Pos) { characterSprite.setPosition(_Pos); characterPosition = _Pos; }
	sf::Vector2f getPosition() { return characterSprite.getPosition(); };

	// TODO - Move to player
	std::string characterName;

	// TODO - Move to player and fix properly. 
	void rotateCharacter(int _Direction);

	// TODO - Remove as convert is in the math library
	// TODO - Add set rotation
	void convertRotation();
	
	// TODO - Make virtual or move into child classes as needed
	void moveCharacter();

	// TODO - Lower upper. 
	// TODO - return pointer instead of value
	sf::Sprite GetSprite();

protected:
	
	// Constant variables. These will not change. Therefore, have been made as const. 

	// TODO - Not const max health. make member variable of child classes
	// TODO - change name as no longer const 
	const float MAX_HEALTH = 100.0f;
	const float MAX_SPEED = 50.0f;
	const float SPEED_SCALAR = 10.0f;


	// TODO - Add m_ for member variables
	// TODO - Add variable types to names to f.. i... etc
	// TODO - Add p for pointer variable names
	float currentHealth;

	sf::RenderWindow* windowRef;

	sf::Sprite characterSprite;
	sf::Texture characterTexture;

	sf::Vector2f characterPosition;
	
	float characterRotation;
	float radiansRotation;

	
};


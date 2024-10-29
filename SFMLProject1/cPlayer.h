/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : cPlayer.h
Description : player class, child of cCharacter.  Contains all methods for the player characters
Author : Daniel Kilfoyle
Mail : DanielKilfoyle@mds.ac.nz
**************************************************************************/

#pragma once
#include "cCharacter.h"
#include "MathLibrary.h"
#include "cLevel.h"
#include "cProjectile.h"
#include "cWand.h" 
#include <string>

class cPlayer : public cCharacter
{
public:
	cPlayer(sf::Sprite* _Sprite, std::string _PlayerName, sf::Vector2f _Position, std::vector<cCharacter*>* _activeCharacters, cLevel& _level);

	void rotateCharacter(sf::Keyboard::Key _key, int _scalar);
	void processInput();
	void movePlayer();

	void castSpell();

	void playerUpdate(float _deltaTime);

	sf::Keyboard::Key leftRotateKey;
	sf::Keyboard::Key rightRotateKey;
	sf::Keyboard::Key forwardMovementKey;
	sf::Keyboard::Key castSpellKey;

	void setProjectileSprite(sf::Sprite* _projectile);
	void setProjectileList(std::vector<cProjectile*>* _projectiles);

	void setProjectileCount(int _count);
	void setFireRate(float _rate);
	void setDamageStrength(float _damage);

	void healthCheck();

	void killPlayer();

	void respawnPlayer();

	void setWandRef(class cWand* _wand);  // Set wand reference
	std::string getCurrentWandName() const;  // Get wand name

	int getPlayerOneOrTwo();

	void setProjectileSound(sf::Sound _sound);

	void setDeathSound(sf::Sound _sound);
	void setIdleSound(sf::Sound _sound);



	


private:
	std::string m_playerName;

	cLevel& level; // Reference to the level for boundary checks
	sf::Sprite m_projectileSprite;
	sf::Clock m_castTimer;
	bool m_bFired;
	std::vector<cProjectile*>* m_projectilesList;

	bool m_bActive = true;
	sf::Vector2f m_previousPosition;
	sf::Clock m_respawnTimer;

	int m_iProjectileCount;
	float m_fFireRate;
	float m_fDamage;

	cWand* m_currentWandRef = nullptr;  // Pointer to current wand

	sf::Sound m_projectileFireSound;
	sf::Sound m_DeathSound;
	sf::Sound m_IdleSound;




};

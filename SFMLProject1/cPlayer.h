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
#include "cSoundManager.h"

class cPlayer : public cCharacter
{
public:
	cPlayer(sf::Sprite* _Sprite, std::string _PlayerName, sf::Vector2f _Position, std::vector<cCharacter*>* _activeCharacters, cLevel& _level);

	void rotateCharacter(sf::Keyboard::Key _key, int _scalar);
	void processInput();
	void movePlayer();

	void castSpell();

	std::string getCurrentWandName() const;

	void setCurrentWand(const std::string& wandName);

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

	int getPlayerOneOrTwo();

	void setSoundManager(cSoundManager* _Sounds);

	void setOtherPlayerRef(cPlayer* _otherPlayer);


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

	std::string currentWandName;
	cWand* m_currentWandRef = nullptr;  // Pointer to current wand

	cSoundManager*  m_Sounds = nullptr;

	cPlayer* m_otherPlayer = nullptr;
};
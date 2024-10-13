/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : cCollisionManager.h
Description : The manager class for all of the collisions in game
Author : Daniel Kilfoyle
Mail : DanielKilfoyle@mds.ac.nz
**************************************************************************/

#pragma once
#include "cCharacter.h"
#include "cPlayer.h"
#include "cEnemy.h"
#include "cProjectile.h"
#include "MathLibrary.h"


class cCollisionManager
{
public:

	cCollisionManager();

	void collisionCheck(std::vector <cCharacter*> _activeCharacters);

	void projectileCheck(std::vector <cCharacter*> _activeCharacters, std::vector <cProjectile*> _activeProjectiles);



};


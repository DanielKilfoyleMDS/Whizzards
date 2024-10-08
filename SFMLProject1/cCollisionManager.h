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


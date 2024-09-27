#include "cEnemy.h"


cEnemy::cEnemy(std::string _FilePath, std::string _CharacterName, sf::Vector2f _StartPosition)
	: cCharacter(_FilePath, _CharacterName, _StartPosition)
{
	//Runs original constructor and then additional logic below

}

cEnemy::~cEnemy()
{
}

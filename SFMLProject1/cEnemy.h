#pragma once
#include "cCharacter.h"

class cEnemy: public cCharacter
{
public:
	cEnemy(std::string _FilePath, std::string _CharacterName, sf::Vector2f _StartPosition);
	~cEnemy();


private:
	float m_fDamage;
	//Attack Style
	//Movement Style


};

//Option A: Subclasses of Enemy
//Option B: references to behaviour classes - such as move style and attack styke
#include "cEnemyBehaviour.h"
#include "cEnemy.h"

/************************************************************************
Name: cEnemyBehaviour
Description : Constructs EnemyBehaviour. Overwritten by Subclasses.
Parameters: None
Returns: None
Author : Jayden Burns
**************************************************************************/
cEnemyBehaviour::cEnemyBehaviour()
{
}

/************************************************************************
Name: ~cEnemyBehaviour
Description : Deconstructs EnemyBehaviour. Overwritten by Subclasses.
Parameters: None
Returns: None
Author : Jayden Burns
**************************************************************************/
cEnemyBehaviour::~cEnemyBehaviour()
{
	m_behaviourSprite = nullptr;
}

/************************************************************************
Name: setBehaviourSprite
Description : sets sprite for this behaviour
Parameters: sf::Sprite* _Reference
Returns: None
Author : Jayden Burns
**************************************************************************/
void cEnemyBehaviour::setBehaviourSprite(sf::Sprite* _reference)
{
	m_behaviourSprite = _reference;
}


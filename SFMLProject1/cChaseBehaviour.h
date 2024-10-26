#pragma once
#include "cEnemyBehaviour.h"

class cChaseBehaviour :public cEnemyBehaviour
{
public:
	cChaseBehaviour();
	~cChaseBehaviour();

	bool tickEnemy(cEnemy* _parent, float _deltaTime) override;

	bool checkDeath(cEnemy* _parent) override;

	bool canAttack(cEnemy* _parent) override;
	void enemyAttack(cEnemy* _parent) override;

	void enemyMove(cEnemy* _parent) override;

	void setupEnemy(cEnemy* _parent, sf::Vector2f _position) override;

	void pickDirection(cEnemy* _parent);



	//Sets either first player or both players when run
	void setPlayers(class cCharacter* _FirstPlayer);
	void setPlayers(class cCharacter* _FirstPlayer, class cCharacter* _SecondPlayer);

	float GetDistanceToPlayer(cEnemy* _parent, cCharacter* _player);
	void ChasePlayer(cEnemy* _parent, cCharacter* _player);

private:
	
	//Player Tracking - tracks nearest of these two
	class cCharacter* m_FirstPlayer = nullptr;
	class cCharacter* m_SecondPlayer = nullptr;
	float maxChaseRange = 300;
};


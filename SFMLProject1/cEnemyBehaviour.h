#pragma once

class cEnemyBehaviour
{
public: 
	cEnemyBehaviour();
	~cEnemyBehaviour();
	

	//Handles Logic
	virtual void TickEnemy(class cEnemy* _Parent);

	//Checks if Enemy can Attack
	virtual bool CanAttack(class cEnemy* _Parent);
	virtual void Attack(class cEnemy* _Parent);

	//Moves Enemy
	virtual void Move(class cEnemy* _Parent);

};


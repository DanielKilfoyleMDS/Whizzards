#pragma once

class cEnemyBehaviour
{
public: 
	cEnemyBehaviour();
	~cEnemyBehaviour();
	

	//Handles Logic
	virtual bool TickEnemy(class cEnemy* _parent);

	virtual bool CheckDeath(cEnemy* _parent);

	//Checks if Enemy can Attack
	virtual bool CanAttack(class cEnemy* _parent);
	virtual void Attack(class cEnemy* _parent);

	//Moves Enemy
	virtual void Move(class cEnemy* _parent);

};


#pragma once
#include "../Enemy/Enemy.h"
#include "AIAction.h"
#include <queue>
#include <vector>
class EnemyAI
{
public:
	EnemyAI(Enemy* e, std::vector<AIAction*>& ListOfActions);
	void Update(float dt);
private:
	std::queue<AIAction*> actions;
	std::vector<AIAction*>& ListOFActions;
	AIAction* CurrentAction;
	Enemy* AttachedEnemy;
};


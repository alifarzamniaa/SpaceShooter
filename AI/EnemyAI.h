#pragma once
#include "../Enemy/Enemy.h"
#include "AIAction.h"
#include <queue>
#include <vector>
class EnemyAI
{
public:
	EnemyAI(std::vector<std::shared_ptr<AIAction>>& ListOfActions);
	void Update(float dt);
	//Cancel the currentAction
	void CancelCurrentAction();
	//cancel the previous action and run the given action once
	void AddTempAction(AIAction* Action);
private:
	std::queue<std::shared_ptr<AIAction>> actions;
	std::vector<std::shared_ptr<AIAction>> actionsList;
	AIAction* CurrentAction;
};


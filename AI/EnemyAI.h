#pragma once
#include "../Enemy/Enemy.h"
#include "AIAction.h"
#include <queue>
#include <vector>
class EnemyAI
{
public:
	EnemyAI(std::vector<std::shared_ptr<AIAction>>& ListOfActions);
	EnemyAI(const Enemy& other) = delete;
	EnemyAI& operator=(const Enemy& other) = delete;
	EnemyAI(EnemyAI&& other);
	EnemyAI& operator=(EnemyAI&& other);
	void Update(float dt);
	~EnemyAI();
private:
	std::queue<std::shared_ptr<AIAction>> actions;
	std::vector<std::shared_ptr<AIAction>> actionsList;
	AIAction* CurrentAction;
};


#pragma once
#include "../AIAction.h"
#include "../../Enemy/Enemy.h"
#include "SFML/Graphics.hpp"
class FireAction : public AIAction
{
public:
	FireAction(Enemy* e);
	//initialize values when a task is started ( it can be empty but the child class needs to have it )
	void Start() override;
	// the task which is going to be excuted every frame
	void Update(float delta) override;
	//cancel the operation and mark it as finished
	void Cancel() override;
	// state of the current task
	bool IsFinished() override;
private:
	Enemy* AttachedEntity;
	bool ActiveState;
	int CurrentFireIndex = 0;
};
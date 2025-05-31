#pragma once
#include "../AIAction.h"
#include "../../Enemy/Enemy.h"
#include <Memory>

class Roam : public AIAction
{
public:
	// - e: the enemy that this action is attached to it ( usually the Ai that manages enemy has it as reference) 
	// - Task Duration : set how much time(in seconds) needs to roam
	// - range : the range of movement in x direction (-range to range from the initPosX position)
	// - LeftRightBound : Horizontal boundaries: left (x-value), right (y-value)
	Roam(Enemy* e, float TaskDuration, float range, float speed,const sf::Vector2f& LeftRightBound);
	//initialize values when a task is started ( it can be empty but the child class needs to have it )
	void Start() override;
	// the task which is going to be excuted every frame
	void Update(float delta) override;
	//cancel the operation and mark it as finished
	void Cancel() override;
	// state of the current task
	bool IsFinished() override;
private:
	std::unique_ptr<Enemy> AttachedEntity; // this gets the entity that this action is attached to it
	float Duration;
	float Elapsed;
	float RangeX;
	float speed;
	float Dir;
	float InitPosX;

	float leftBound;
	float rightBound;
	float topBound;
	float bottomBound;
	bool ActiveState;
};


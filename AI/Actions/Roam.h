#pragma once
#include "../AIAction.h"
#include "../../Entity.h"
#include "../../Props/Pool.h"
#include <Memory>

//TODO make the movement function works with these enums
// I'm gonna use function variable and base on this enum, update() will call the func var
enum MovementFuncType
{
	linearMove,
	sinMove,
	circularMove,
	diagonalMove,
	spiralMove
};
class Roam : AIAction
{
public:
	// - e: the entity that this action is attached to it ( usually the Ai that manages enemy has it as reference) 
	// - Task Duration : set how much time(in seconds) needs to roam
	// - range : the range of movement in x direction (-range to range from the current position)
	Roam(Entity* e,float TaskDuration,float range,float speed);
	//initialize values when a task is started ( it can be empty but the child class needs to have it )
	void Start() override;
	// the task which is going to be excuted every frame
	void Update(float delta) override;
	//cancel the operation and mark it as finished
	void Cancel() override;
	// state of the current task
	bool IsFinished() override;
private:
	std::unique_ptr<Entity> AttachedEntity; // this gets the entity that this action is attached to it
	float Duration;
	float Elapsed;
	float RangeX;
	float speed; 
	float Dir;
	float InitPosX;
	bool ActiveState;
};


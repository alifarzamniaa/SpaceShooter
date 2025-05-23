#pragma once
class AIAction
{
public:
	//initialize values when a task is started ( it can be empty but the child class needs to have it )
	virtual void Start() = 0;
	// the task which is going to be excuted every frame
	virtual void Update(float delta) = 0;
	//cancel the operation and mark it as finished
	virtual void Cancel() = 0;
	// state of the current task
	virtual bool IsFinished() = 0;
};
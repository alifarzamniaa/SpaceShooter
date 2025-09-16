#pragma once
#include "../AIAction.h"
#include "../../Enemy/Enemy.h"

enum WaveDirection
{
	XWave,
	YWave
};
struct WaveRoamProp
{
	float TaskDuration;

	//leave it 0 if you use XWave
	float MinRangeX;
	//leave it 0 if you use XWave
	float MaxRangeX;
	//leave it 0 if you use YWave
	float MinRangeY;
	//leave it 0 if you use YWave
	float MaxRangeY;
	//controls how quickly the oscillation occurs. A higher frequency results in faster movement.
	float frequency;
	//determines the range of the oscillation.A higher amplitude means a wider range of movement.
	float amplitude;
	float speed;
	//determines the wave movement direction
	WaveDirection dir;
	
};
class WaveRoam : public AIAction
{
public:
	// - e: the enemy that this action is attached to it ( usually the Ai that manages enemy has it as reference) 
	// - Task Duration : set how much time(in seconds) needs to roam
	// - range : the range of movement in x direction (-range to range from the initPosX position)
	WaveRoam(Enemy* e, const WaveRoamProp& prop);
	//initialize values when a task is started ( it can be empty but the child class needs to have it )
	void Start() override;
	// the task which is going to be excuted every frame
	void Update(float delta) override;
	//cancel the operation and mark it as finished
	void Cancel() override;
	// state of the current task
	bool IsFinished() override;
private:
	void XWave(float delta);
	void YWave(float delta);
private:
	Enemy* AttachedEntity; // this gets the entity that this action is attached to it
	float Elapsed;
	float SinElapsed;
	WaveRoamProp props;
	float DirX;
	float DirY;
	float sinDir;
	float InitPosX;
	Boundary wallBound;
	bool ActiveState;
};


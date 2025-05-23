#include "EnemyAI.h"

EnemyAI::EnemyAI(Enemy* e,std::vector<AIAction*>& ListOfActions)
	:
	AttachedEnemy(e),
	ListOFActions(ListOFActions)
{
	CurrentAction = nullptr;
}

void EnemyAI::Update(float dt)
{	
	if(actions.size() == 0)
	{
		for(auto& a : ListOFActions)
		{
			actions.push(a);
		}
	}
	if(!CurrentAction)
	{
		// get current task from queue
		CurrentAction = actions.front();
		CurrentAction->Start();
	}
	else
	{
		CurrentAction->Update(dt);
		if(CurrentAction->IsFinished())
		{
			CurrentAction = nullptr;
			//go to next action by popping the previous one
			actions.pop();
		}
	}
}
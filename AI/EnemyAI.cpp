#include "EnemyAI.h"

EnemyAI::EnemyAI(std::vector<std::shared_ptr<AIAction>>& ListOfActions)
	:
	actionsList(std::move(ListOfActions))
{
	CurrentAction = nullptr;
}
void EnemyAI::Update(float dt)
{	
	if(actions.size() == 0)
	{
		for(auto& a : actionsList)
		{
			actions.push(a);
		}
	}else
	{
		if (!CurrentAction)
		{
			// get current task from queue
			CurrentAction = actions.front().get();
			CurrentAction->Start();
		}
		else
		{
			CurrentAction->Update(dt);
			if (CurrentAction->IsFinished())
			{
				CurrentAction = nullptr;
				//go to next action by popping the previous one
				actions.pop();
			}
		}
	}
	
}
#include "EnemyAI.h"
#include <iostream>
EnemyAI::EnemyAI(std::vector<std::shared_ptr<AIAction>>& ListOfActions)
	:
	actionsList(std::move(ListOfActions))
{
	CurrentAction = nullptr;
}
void EnemyAI::Update(float dt)
{	
	if(actions.size() == 0 && !CurrentAction)
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

void EnemyAI::CancelCurrentAction()
{
	if(CurrentAction)
		CurrentAction->Cancel();
}

void EnemyAI::AddTempAction(AIAction* Action)
{
	if(Action)
	{
		CancelCurrentAction();
		CurrentAction = nullptr;
		CurrentAction = Action;
		CurrentAction->Start();
	}else
	{
		std::cout << "!!NOT A Valid Action\n";
	}
}

void EnemyAI::Reset()
{
	while(!actions.empty())
	{
		actions.pop();
	}
	CancelCurrentAction();
	CurrentAction = nullptr;
	for (auto& a : actionsList)
	{
		actions.push(a);
	}
}

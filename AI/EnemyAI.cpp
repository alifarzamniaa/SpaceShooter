#include "EnemyAI.h"

EnemyAI::EnemyAI(std::vector<std::shared_ptr<AIAction>>& ListOfActions)
	:
	actionsList(std::move(ListOfActions))
{
	CurrentAction = nullptr;
}

EnemyAI::EnemyAI(EnemyAI&& other)
	:
	CurrentAction(other.CurrentAction)
{
	other.CurrentAction = nullptr;
}

EnemyAI& EnemyAI::operator=(EnemyAI&& other)
{
	if(this != &other)
	{
		delete CurrentAction;//freeing the existing one
		CurrentAction = other.CurrentAction;
		other.CurrentAction = nullptr;//freeing other resource
	}
	return *this;
}

void EnemyAI::Update(float dt)
{	
	if(actions.size() == 0)
	{
		for(auto& a : actionsList)
		{
			actions.push(a);
		}
	}
	if(!CurrentAction)
	{
		// get current task from queue
		CurrentAction = actions.front().get();
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

EnemyAI::~EnemyAI()
{
	delete CurrentAction;
	CurrentAction = nullptr;
}

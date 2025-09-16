#pragma once
#include "../AIAction.h"
#include "../../Enemy/Enemy.h"
#include "SFML/Graphics.hpp"
#include <functional>
class MoveTo : public AIAction
{
public:
	MoveTo(Enemy* e,const std::function<sf::Vector2f()>& Location);
	//initialize values when a task is started ( it can be empty but the child class needs to have it )
	void Start() override;
	// the task which is going to be excuted every frame
	void Update(float delta) override;
	//cancel the operation and mark it as finished
	void Cancel() override;
	// state of the current task
	bool IsFinished() override;
private:
	Enemy* AttachedEntity; // this gets the entity that this action is attached to it
	std::function<sf::Vector2f()> GetLocationFunc;
	sf::Vector2f locToMove;
	sf::Vector2f NormalizedDir;
	sf::Vector2f Dir;
	Boundary wallBound;
	float speed;
	bool IsActiveState = false;
};
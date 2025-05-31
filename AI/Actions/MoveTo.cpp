#include "MoveTo.h"

MoveTo::MoveTo(Enemy* e, const std::function<sf::Vector2f()>& Location)
	:
	AttachedEntity(e),
	GetLocationFunc(Location)
{
	speed = AttachedEntity ? AttachedEntity->GetSpeed() : 0;
}

void MoveTo::Start()
{
	IsActiveState = true;
	locToMove = GetLocationFunc();
	Dir = locToMove - AttachedEntity->GetPosition();
}

void MoveTo::Update(float delta)
{
	if(AttachedEntity && IsActiveState)
	{
		sf::Vector2f vel = Dir.normalized() * speed * delta;
		sf::Vector2f distance = locToMove - AttachedEntity->GetPosition();
		AttachedEntity->SetPosition(AttachedEntity->GetPosition().x + vel.x, AttachedEntity->GetPosition().y + vel.y);
		if(distance.length() < 1.f || !AttachedEntity->IsInWallBoundary())
			Cancel();
	}
}

void MoveTo::Cancel()
{
	IsActiveState = false;
}

bool MoveTo::IsFinished()
{
	return !IsActiveState;
}

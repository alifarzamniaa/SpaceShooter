#include "MoveTo.h"
#include <iostream>

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
	NormalizedDir = Dir.length() != 0.0f ? Dir.normalized() : sf::Vector2f(0.0f, 0.0f);
	wallBound = AttachedEntity->WallBoundary();
}

void MoveTo::Update(float delta)
{
	if(AttachedEntity && IsActiveState)
	{
		sf::Vector2f distance = locToMove - AttachedEntity->GetPosition();
		Boundary eBound = AttachedEntity->entityBoundary();
		bool CustomWallBound = eBound.left <= wallBound.right && eBound.right >= wallBound.left && eBound.top <= wallBound.bottom;
		if(CustomWallBound && std::abs(distance.length()) > 1.f)
		{
			//using std::min to make sure we dont overshoot 
			sf::Vector2f vel = NormalizedDir * std::min(speed * delta,distance.length());
			AttachedEntity->SetPosition(AttachedEntity->GetPosition().x + vel.x, AttachedEntity->GetPosition().y + vel.y);
			AttachedEntity->SetMoving(true);
		}else
			Cancel();
	}
}

void MoveTo::Cancel()
{
	IsActiveState = false;
	AttachedEntity->SetMoving(false);
}

bool MoveTo::IsFinished()
{
	return !IsActiveState;
}

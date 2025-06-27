#include "FireAction.h"
#include <iostream>
FireAction::FireAction(Enemy* e)
	:
	AttachedEntity(e)
{
	ActiveState = false;
}

void FireAction::Start()
{
	ActiveState = true;
	CurrentFireIndex = 0;
	if (AttachedEntity)
		AttachedEntity->SetFiringState(true);
}

void FireAction::Update(float delta)
{
	if(ActiveState)
	{
		if(AttachedEntity)
		{
			assert(!AttachedEntity->GetFrameOfFire().empty()); // fill the frame to fire in the enemy class
			if(CurrentFireIndex < AttachedEntity->GetFrameOfFire().size() &&
			   AttachedEntity->GetFireCurrentFrame() == AttachedEntity->GetFrameOfFire().at(CurrentFireIndex)
			)
			{
				assert(!AttachedEntity->GetSockets().empty()); //You dont have a socket ,fill the sockets vector first
				AttachedEntity->RetrieveBullet();
				auto bullets = AttachedEntity->GetBullets();
				if(bullets[CurrentFireIndex])
				{
					
					sf::Vector2f MuzzleLocation = AttachedEntity->GetPosition() + AttachedEntity->GetSockets().at(CurrentFireIndex);
					bullets[CurrentFireIndex]->SetPosition(MuzzleLocation.x, MuzzleLocation.y);
					bullets[CurrentFireIndex]->SetDirection(AttachedEntity->GetShootDir());
					bullets[CurrentFireIndex]->SetActive(true);
				}
				CurrentFireIndex++;
			}
			if(!AttachedEntity->IsFiring())
			{
				Cancel();
			}
		}
	}
}

void FireAction::Cancel()
{
	ActiveState = false;
}

bool FireAction::IsFinished()
{
	return !ActiveState;
}

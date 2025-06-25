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
			if(CurrentFireIndex < AttachedEntity->GetFrameOfFire().size() &&
			   AttachedEntity->GetFireCurrentFrame() == AttachedEntity->GetFrameOfFire().at(CurrentFireIndex)
			)
			{
				AttachedEntity->RetrieveBullet();
				auto bullets = AttachedEntity->GetBullets();
				if(bullets[CurrentFireIndex])
				{
					sf::Vector2f MuzzleLocation = AttachedEntity->GetPosition() + AttachedEntity->GetSockets().at(CurrentFireIndex);
					bullets[CurrentFireIndex]->SetPosition(MuzzleLocation.x, MuzzleLocation.y);
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

#include "Roam.h"
#include <math.h>
#include <iostream>
Roam::Roam(Entity* e, float TaskDuration, float range, float speed)
    :
    Duration(TaskDuration),
    RangeX(range),
    speed(speed),
    AttachedEntity(e)
{
     ActiveState = false;
}

void Roam::Start()
{
    ActiveState = true;
    Elapsed = 0.0f;
    InitPosX = AttachedEntity->GetPosition().x;
    Dir = 1; //goes right
}

void Roam::Update(float delta)
{
    if(ActiveState)
    {
        Elapsed += delta;
        if (Elapsed >= Duration)
        {
            Cancel();
        }else
        {
            if (AttachedEntity)
            {
                float CurrentPos = AttachedEntity->GetPosition().x;
                if (CurrentPos >= InitPosX + RangeX || CurrentPos <= InitPosX - RangeX)
                    Dir *= -1;
                float vel = Dir * speed * delta;
                AttachedEntity->SetPosition(CurrentPos + vel , AttachedEntity->GetPosition().y);
            }
            else
               std::cout << "Entity is Not Attached(it is NULL) !!\n";
        }
    }
}

void Roam::Cancel()
{
    ActiveState = false;
}

bool Roam::IsFinished()
{
    return !ActiveState;
}

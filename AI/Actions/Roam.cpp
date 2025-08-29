#include "Roam.h"
#include <math.h>
#include <iostream>
Roam::Roam(Enemy* e, float TaskDuration, float MinRangeX, float MaxRangeX, float speed, const sf::Vector2f& LeftRightBound)
    :
    Duration(TaskDuration),
    MinRangeX(MinRangeX),
    MaxRangeX(MaxRangeX),
    speed(speed),
    AttachedEntity(e)
{
    ActiveState = false;
    leftBound = LeftRightBound.x;
    rightBound = LeftRightBound.y;
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

                float EnemyLeft = CurrentPos - AttachedEntity->GetSize().x / 2 + AttachedEntity->GetTextureOffsetX();
                float EnemyRight = CurrentPos + AttachedEntity->GetSize().x / 2 - AttachedEntity->GetTextureOffsetX();
                if (!AttachedEntity->IsInWallBoundary() && (EnemyLeft <= MinRangeX || EnemyRight >= MaxRangeX ))
                    Dir *= -1;
                float vel = Dir * speed * delta;
                AttachedEntity->SetPosition(CurrentPos + vel, AttachedEntity->GetPosition().y);
                AttachedEntity->SetMoving(true);
            }
            else
               std::cout << "Entity is Not Attached(it is NULL) !!\n";
        }
    }
}

void Roam::Cancel()
{
    ActiveState = false;
    if(AttachedEntity)
        AttachedEntity->SetMoving(false);
}

bool Roam::IsFinished()
{
    return !ActiveState;
}

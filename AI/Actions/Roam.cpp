#include "Roam.h"
#include <math.h>
#include <iostream>
Roam::Roam(Enemy* e, float TaskDuration, float range, float speed, const sf::Vector2f& LeftRightBound)
    :
    Duration(TaskDuration),
    RangeX(range),
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

                if (CurrentPos >= InitPosX + RangeX || CurrentPos <= InitPosX - RangeX || 
                    EnemyLeft <= leftBound || EnemyRight >= rightBound
                )
                    Dir *= -1;
                float vel = Dir * speed * delta;
                AttachedEntity->SetPosition(CurrentPos + vel, AttachedEntity->GetPosition().y);
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

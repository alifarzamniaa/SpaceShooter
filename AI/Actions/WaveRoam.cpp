#include "WaveRoam.h"
#include <math.h>
#include <iostream>

WaveRoam::WaveRoam(Enemy* e, const WaveRoamProp& prop)
    :
    props(prop),
    AttachedEntity(e)
{
    ActiveState = false;
}

void WaveRoam::Start()
{
    ActiveState = true;
    Elapsed = 0.0f; 
    SinElapsed = 0.0f;
    DirX = 1; //goes right
    DirY = 1; //goes down
    sinDir = 1;

    if(AttachedEntity)
    {
        InitPosX = AttachedEntity->GetPosition().x;
        wallBound = AttachedEntity->WallBoundary();
    }
    else
    {
        std::cout << "Entity is not attached in WaveRoam at Start\n";
    }
}
void WaveRoam::XWave(float delta)
{
    Elapsed += delta;
    if (Elapsed >= props.TaskDuration)
    {
        Cancel();
    }
    else
    {
        if (AttachedEntity)
        {
            SinElapsed += delta * sinDir;
            sf::Vector2f CurrentPos = AttachedEntity->GetPosition();

            Boundary eBoundary = AttachedEntity->entityBoundary();

            if (eBoundary.bottom > props.MaxRangeY)
                DirY = -1;

            if (eBoundary.top < props.MinRangeY)
                DirY = 1;

            float velY = DirY * props.speed * delta;

            float velX = (std::sin(SinElapsed * props.frequency)) * props.amplitude;
            AttachedEntity->SetPosition(CurrentPos.x + velX, CurrentPos.y + velY);
            float width = (eBoundary.right - eBoundary.left) / 2.f + 1.f;
            if (eBoundary.right >= wallBound.right)
            {
                AttachedEntity->SetPosition(wallBound.right - width, CurrentPos.y + velY);
                sinDir = -1;
            }
            if(eBoundary.left <= wallBound.left)
            {
                AttachedEntity->SetPosition(wallBound.left + width, CurrentPos.y + velY);
                sinDir = 1;
            }
            
            AttachedEntity->SetMoving(true);

        }
        else
            std::cout << "Entity is Not Attached(it is NULL) !!\n";
    }
}

void WaveRoam::YWave(float delta)
{
    Elapsed += delta;
    if (Elapsed >= props.TaskDuration)
    {
        Cancel();
    }
    else
    {
        if (AttachedEntity)
        {
            sf::Vector2f CurrentPos = AttachedEntity->GetPosition();
            Boundary eBoundary = AttachedEntity->entityBoundary();
            if (wallBound.IsContain(eBoundary) && (eBoundary.left <= props.MinRangeX || eBoundary.right >= props.MaxRangeX))
                DirX *= -1;


            float velX = DirX * props.speed * delta;
            float velY = (std::sin(Elapsed * props.frequency)) * props.amplitude;

            AttachedEntity->SetPosition(CurrentPos.x + velX, CurrentPos.y + velY);
            AttachedEntity->SetMoving(true);

        }
        else
            std::cout << "Entity is Not Attached(it is NULL) !!\n";
    }
}

void WaveRoam::Update(float delta)
{
    if (ActiveState)
    {
        if (props.dir == WaveDirection::XWave)
        {
            XWave(delta);
        }
        if (props.dir == WaveDirection::YWave)
        {
            YWave(delta);
        }
    }
}

void WaveRoam::Cancel()
{
    ActiveState = false;
    if (AttachedEntity)
        AttachedEntity->SetMoving(false);
}

bool WaveRoam::IsFinished()
{
    return !ActiveState;
}



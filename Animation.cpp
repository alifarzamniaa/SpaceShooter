#include "Animation.h"

Animation::Animation(int FrameWidth, int Frameheight, int FrameCount, float FrameDuration)
	:
	CurrentFrameIndex(0),
	FDuration(FrameDuration),
	nFrame(FrameCount)
{
	for(int i = 0; i < nFrame;i++)
	{
		Frames.push_back(sf::IntRect({ FrameWidth * i,0},{ FrameWidth,Frameheight}));
	}
}

void Animation::Update(float delta)
{
	if(CurrentTime <= FDuration)
		CurrentTime += delta;
	else 
	{
		if(CurrentFrameIndex < nFrame - 1)
		{
			isFinished = false;
			CurrentFrameIndex++;
			CurrentTime = 0;
		}
		else
		{
				CurrentFrameIndex = 0;
				isFinished = true;
		}
	}
}

sf::IntRect Animation::GetCurrentFrame() const
{
	return Frames[CurrentFrameIndex];
}

int Animation::GetCurrentIndex() const
{
	return CurrentFrameIndex;
}

bool Animation::IsAnimFinished() const
{
	return isFinished;
}


#include "Animation.h"

Animation::Animation(int FrameWidth, int Frameheight, int FrameCount, float FrameDuration,bool isLooped)
	:
	CurrentFrameIndex(0),
	FDuration(FrameDuration),
	Looped(isLooped),
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
			CurrentFrameIndex++;
			CurrentTime = 0;
		}
		else
		{
			if(!Looped)
				CurrentFrameIndex = nFrame - 1;
			else
				CurrentFrameIndex = 0;
		}
	}
}

sf::IntRect Animation::GetCurrentFrame()
{
	return Frames[CurrentFrameIndex];
}


#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class Animation
{
public:
	Animation(int width,int height,int FrameCount,float animDuration);
	void Update(float delta);
	sf::IntRect GetCurrentFrame();
	bool IsAnimFinished() const;
private:
	std::vector<sf::IntRect> Frames;
	// Duration of each frame
	float FDuration; 
	float CurrentTime = 0.f;
	int nFrame;
	int CurrentFrameIndex;
	bool isFinished = false;
};
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class Animation
{
public:
	Animation(int width,int height,int FrameCount,float animDuration,bool isLooped);
	void Update(float delta);
	sf::IntRect GetCurrentFrame();
private:
	std::vector<sf::IntRect> Frames;
	float FDuration; // Duration of each frame
	float CurrentTime = 0.f;
	int nFrame;
	int CurrentFrameIndex;
	bool Looped;
};


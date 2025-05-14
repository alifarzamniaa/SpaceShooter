#include "Background.h"
#include <iostream>

Background::Background(const sf::RenderWindow& window, float speed)
	:
	speed(speed)
{
	bgsTexture.resize(4);
	if(!bgsTexture[0].loadFromFile("Images/Background/bg1.png"))
	{
		std::cout << "bg1 is not loaded into bgsTexture[0]!!\n";
	}
	if (!bgsTexture[1].loadFromFile("Images/Background/bg2.png"))
	{
		std::cout << "bg2 is not loaded into bgsTexture[1]!!\n";
	}
	if (!bgsTexture[2].loadFromFile("Images/Background/bg3.png"))
	{
		std::cout << "bg3 is not loaded into bgsTexture[2]!!\n";
	}
	if (!bgsTexture[3].loadFromFile("Images/Background/bg4.png"))
	{
		std::cout << "bg4 is not loaded into bgsTexture[3]!!\n";
	}
	for(int i = 0; i < 4;i++)
	{
		// i adjust this 1500 hard coded value from calculating ratio , from 2048w,4096h to 750w, 1500h
		bgs.emplace_back(sf::Vector2f((float)window.getSize().x,1500));

		//set each box on top of each other like = 0 * height , -1 * height , ...
		bgs[i].setPosition({0,(float) -i * bgs[i].getSize().y});
		bgs[i].setTexture(&bgsTexture[i]);
	}
}

void Background::Update(float delta,const sf::RenderWindow& window)
{
	float s = speed * delta;
	for(int i = 0; i < bgs.size(); i++)
	{
		bgs[i].move({0,s});
		
		if (bgs[i].getPosition().y > window.getSize().y)
		{
			float minPos = bgs[i].getPosition().y;
			for(int j = 0; j < bgs.size();j++)
				minPos = std::min(minPos,bgs[j].getPosition().y); // find the position of the top item (who has the lowest value in them)
			
			bgs[i].setPosition({ bgs[i].getPosition().x,minPos - bgs[i].getSize().y + 1}); // add this on top of that ( +1 for picture pos adjustment) 
		}
	}
}

void Background::Draw(sf::RenderWindow& window)
{
	for (auto& b : bgs)
		window.draw(b);
}

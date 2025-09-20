#include "PlayerHealth.h"
#include <iostream>
PlayerHealth::PlayerHealth(const sf::Vector2f pos,float PlayerHP)
{
	healthBarPath = "Images/UI/Health_Bar_Table.png";
	healthDotPath = "Images/UI/Health_Dot.png";

	// this shows each dot indicate what amount of HP
	HPAmountOfEachDot = 10;
	PlayerDotNum = (int)PlayerHP / HPAmountOfEachDot;

	//shrink down the inner health dot rectangle size by this padding in  Y
	float DotSizePaddingY = 12.f;
	//shrink down the inner health dot rectangle size by this padding in X
	DotSizePaddingX = 50.f;


	float DotPositionPaddingY = 7.f;

	float DotPositionPaddingX = 8.f;


	heightOfHealthBar = 50.f;

	// this shrinks the width of health UI dot image
	DotWidthScaleDown = 2;
	// 30 and 58 is the size of the texture we load in its hard coded here
	WidthOfEachDot = 30 / DotWidthScaleDown;
	heightOfEachDot = 58;

	healthBar.setSize({ (float)PlayerDotNum * WidthOfEachDot + DotSizePaddingX,heightOfHealthBar });
	healthDot.setSize({ (float)PlayerDotNum * WidthOfEachDot, heightOfHealthBar - DotSizePaddingY });
	healthBar.setPosition(pos);
	healthDot.setPosition({pos.x + DotPositionPaddingX,pos.y + DotPositionPaddingY });

	if(HealthBarTex.loadFromFile(healthBarPath))
	{
		healthBar.setTexture(&HealthBarTex);
	}
	else
	{
		std::cout << "COULD NOT LOAD HEALTH BAR TEXTURE maybe Check path\n";
	}
	if (HealthDotTex.loadFromFile(healthDotPath))
	{
		healthDot.setTexture(&HealthDotTex);
		HealthDotTex.setRepeated(true);
		healthDot.setTextureRect(sf::IntRect({0,0},{PlayerDotNum * WidthOfEachDot * DotWidthScaleDown,heightOfEachDot}));
	}
	else
	{
		std::cout << "COULD NOT LOAD HEALTH DOT TEXTURE maybe Check path\n";
	}
}
void PlayerHealth::Draw(sf::RenderWindow& window)
{
	window.draw(healthBar);
	if(healthDot.getSize().x > 0)
		window.draw(healthDot);
}
void PlayerHealth::onHealthChange(float HealthVal)
{
	int HealthNum = (HealthVal / HPAmountOfEachDot) - PlayerDotNum;
	PlayerDotNum += HealthNum;
	if(PlayerDotNum * WidthOfEachDot < healthBar.getSize().x - DotSizePaddingX)
	{
		healthDot.setSize({ (float)PlayerDotNum * WidthOfEachDot,healthDot.getSize().y });
	}
	healthDot.setTextureRect(sf::IntRect({ 0,0 }, { (PlayerDotNum * WidthOfEachDot * DotWidthScaleDown),heightOfEachDot}));
}



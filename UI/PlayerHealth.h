#pragma once
#include "SFML/Graphics.hpp"
class PlayerHealth
{
public:
	PlayerHealth(const sf::Vector2f pos,float PlayerHP);
	void Draw(sf::RenderWindow& window);
	void onHealthChange(float HealthVal);
private:
	sf::RectangleShape healthBar;
	sf::RectangleShape healthDot;

	std::string healthBarPath;
	std::string healthDotPath;

	sf::Texture HealthBarTex;
	sf::Texture HealthDotTex;
	int HPAmountOfEachDot;
	int WidthOfEachDot;
	int heightOfEachDot;
	int PlayerDotNum;
	int DotWidthScaleDown;
	float DotSizePaddingX;
	float heightOfHealthBar;
};
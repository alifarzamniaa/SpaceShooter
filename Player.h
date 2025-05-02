#pragma once
#include <SFML/Graphics.hpp>
#include "SpaceShip.h"
class Player
{
public:
	Player(const sf::Vector2f& pos);	
	void Draw(sf::RenderWindow& window);
private:
	//Custom Properties
	std::string BaseImgPath = "Images/Player/Base.png";
	std::string EngineImgPath = "Images/Player/Engine.png";
	std::string ShieldImgPath = "Images/Player/Shield.png";
	int health = 100;
	float PlayerShipSize = 100.f;
	
	SpaceShip sp;
};


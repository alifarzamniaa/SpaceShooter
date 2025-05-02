#pragma once
#include <SFML/Graphics.hpp>
#include "SpaceShip.h"
#include "Animation.h"
class Player
{
public:
	Player(const sf::Vector2f& pos);	
	void Draw(sf::RenderWindow& window, float delta);
	void Movement(float delta, const sf::Vector2f& leftRightBound, const sf::Vector2f& TopBottomBound);
	void WallCollision(const sf::Vector2f& leftRightBound, const sf::Vector2f& topBottomBound);
private:
	//Custom Properties
	std::string BaseImgPath = "Images/Player/Weapon.png";
	std::string EngineImgPath = "Images/Player/Engine.png";
	std::string ShieldImgPath = "Images/Player/Shield.png";
	float verticalPadding = 20.f;//this is used for if texture is smaller than the box, you can adjust the gap between box and texture to make collision more accurate
	float horizontalPadding = 15.f; // same as above but for horizontal part


	int health = 100;
	float playerShipSize = 100.f;
	float speed = 500.f;
	float ShieldCooldown = 20.f; // in seconds
	float ShieldDuration = 5.f; // in seconds
	
	//obj
	SpaceShip sp;
	Animation EngineAnim;
	Animation ShieldAnim;
};


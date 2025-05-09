#pragma once
#include <SFML/Graphics.hpp>
#include "Props/SpaceShip.h"
#include "Animation.h"
#include "Bullets.h"
class Player
{
public:
	Player(const sf::Vector2f& pos);	
	void Draw(sf::RenderWindow& window, float delta);
	void Movement(float delta, const sf::Vector2f& leftRightBound, const sf::Vector2f& TopBottomBound);
	void WallCollision(const sf::Vector2f& leftRightBound, const sf::Vector2f& topBottomBound);
	
	sf::Texture& GetBulletTex();
	Animation GetBulletAnim();
	
private:
	//Custom Properties
	std::string BaseImgPath = "Images/Player/Weapon.png";
	std::string EngineImgPath = "Images/Player/Engine.png";
	std::string ShieldImgPath = "Images/Player/Shield.png";
	std::string BulletImgPath = "Images/Bullets/PlayerBullet.png";

	//this is used for if texture is smaller than the box, you can adjust the gap between box and texture to make collision more accurate
	float verticalPadding = 20.f;
	// same as vertical but for horizontal part
	float horizontalPadding = 15.f;


	int health = 100;
	float playerShipSize = 100.f;
	float speed = 500.f;
	float ShieldCooldown = 20.f; // in seconds
	float ShieldDuration = 5.f; // in seconds

	//change its value on constructor
	sf::Vector2f BulletSocket;
	
	//obj
	SpaceShip sp;
	sf::Texture BulletTex;
	Animation EngineAnim;
	Animation ShieldAnim;
	Animation BulletAnim;
	Bullets Bullet;
};


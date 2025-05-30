#pragma once
#include "../Entity.h"
#include "../Props/SpaceShip.h"
#include "../Props/Pool.h"
#include "../Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>


struct AnimData
{
	int FrameWidth;
	int FrameHeight;
	int NumberOfFrames;
	float AnimDuration;
	std::string Path;
};
struct EnemyData
{
	AnimData FireAnim;
	AnimData EngineAnim;
	AnimData ShieldAnim;
	AnimData DestructAnim;

	int health;
	float speed;
};
class Enemy : public Entity
{
public:
	Enemy(sf::RenderWindow& windowRef, Player& player,const sf::Vector2f& pos,const EnemyData& data)
	:
		windowRef(windowRef),
		player(player),
		BaseImgPath(data.FireAnim.Path),
		EngineImgPath(data.EngineAnim.Path),
		ShieldImgPath(data.ShieldAnim.Path),
		DestructionImgPath(data.DestructAnim.Path),
		FiringAnim(data.FireAnim.FrameWidth,data.FireAnim.FrameHeight,data.FireAnim.NumberOfFrames,data.FireAnim.AnimDuration),
		EngineAnim(data.EngineAnim.FrameWidth,data.EngineAnim.FrameHeight,data.EngineAnim.NumberOfFrames,data.EngineAnim.AnimDuration),
		ShieldAnim(data.ShieldAnim.FrameWidth,data.ShieldAnim.FrameHeight,data.ShieldAnim.NumberOfFrames,data.ShieldAnim.AnimDuration),
		DestructionAnim(data.DestructAnim.FrameWidth, data.DestructAnim.FrameHeight ,data.DestructAnim.NumberOfFrames,data.DestructAnim.AnimDuration),
		health(data.health),
		speed(data.speed),
		sp(pos,data.FireAnim.Path,data.EngineAnim.Path,data.ShieldAnim.Path,data.DestructAnim.Path)
	{
	};
	virtual void SetShieldState(bool in_State) = 0;
	virtual void SetDestroyedState(bool in_State) = 0;
	virtual bool IsDestroyed() const = 0;
	// Returns the horizontal offset needed for accurate collision detection,
	// in case the texture size doesn't match the visual rectangle size.
	// returns 0 if texture is the same size as the rectangle
	virtual float GetTextureOffsetX() const = 0;
	// Returns the vertical offset needed for accurate collision detection,
	// in case the texture size doesn't match the visual rectangle size.
	// returns 0 if texture is the same size as the rectangle
	virtual float GetTextureOffsetY() const = 0;

	virtual ~Enemy() = default;
protected:
	// logic for destruction and when health is <= 0 
	virtual void DestructionEvent(float delta) = 0;
protected:
	std::string BaseImgPath;
	std::string EngineImgPath;
	std::string ShieldImgPath;
	std::string DestructionImgPath;

	Animation FiringAnim;
	Animation EngineAnim;
	Animation ShieldAnim;
	Animation DestructionAnim;

	float health;
	float speed;

	sf::RenderWindow& windowRef;
	Player& player;
	SpaceShip sp;

};


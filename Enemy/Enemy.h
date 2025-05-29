#pragma once
#include "../Entity.h"
#include "../Props/SpaceShip.h"
#include "../Props/Pool.h"
#include "../Player.h"
#include <SFML/Graphics.hpp>
class Enemy : public Entity
{
public:
	Enemy(sf::RenderWindow& windowRef, Player& player)
	:
		windowRef(windowRef),
		player(player)
	{};
	virtual void SetShieldState(bool in_State) = 0;
	virtual void SetDestroyedState(bool in_State) = 0;
	virtual bool IsDestroyed() const = 0;
	// texture may not be the same size as rect itself and may cause to inaccurate collision
	// this returns horizontal offset used to adjust collision detection
	// returns 0 if texture is the same size as the rectangle
	virtual float GetTextureOffsetX() const = 0;
	// texture may not be the same size as rect itself and may cause to inaccurate collision
	// this returns vertical offset used to adjust collision detection
	// returns 0 if texture is the same size as the rectangle
	virtual float GetTextureOffsetY() const = 0;

protected:
	sf::RenderWindow& windowRef;
	Player& player;
	
};


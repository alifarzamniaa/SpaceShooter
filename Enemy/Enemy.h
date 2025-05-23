#pragma once
#include "../Entity.h"
#include "../Props/SpaceShip.h"
#include "../Props/Pool.h"
#include <SFML/Graphics.hpp>
class Enemy : public Entity
{
public:
	virtual void Fire(float delta, Pool& bulletPool) = 0;
	virtual void Movement(float dt) = 0;

};


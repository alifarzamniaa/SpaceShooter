#pragma once
#include "SFML/Graphics.hpp"
#include "BulletResource.h"
#include "../Pool.h"
#include "Bullets.h"

class BulletManager
{
public:
	BulletManager(int& id,Grid& grid,sf::RenderWindow& window);
	void Draw();
	void Update(float delta);
	Pool& GetPlayerBulletPool();
	Pool& GetFighterBulletPool();
	Pool& GetEliteFighterBulletPool();
private:
	void DrawPools(Pool& pool);
	void UpdatePools(Pool& pool, float delta);
private:
	Grid& grid;
	sf::RenderWindow& window;
	int& id;
	BulletResource bulltetResource;
	Pool playerBulletPool;
	Pool fighterBulletPool;
	Pool eliteFighterBulletPool;
};
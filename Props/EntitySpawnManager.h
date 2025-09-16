#pragma once
#include "SFML/Graphics.hpp"
#include "Pool.h"
#include "../Player.h"
#include "Projectile/BulletResource.h"
#include "Projectile/BulletManager.h"
#include "Grid.h"
#include "../Enemy/Type1/Fighter.h"
#include "../Enemy/Type1/EliteFighter.h"
#include <random>

class EntitySpawnManager
{
public:
	EntitySpawnManager(int& id,Player& player,Grid& grid, sf::RenderWindow& window, BulletManager& bulletMg);
	void Draw();
	void Update(float delta);
	void SpawnEnemy();


private:
	void DrawPools(Pool& pool);
	void UpdatePools(Pool& pool,float delta);
	void SpawnLogic(int& remainingNumber,int enemyNumber, Pool& pool, std::vector<Entity*>& list);
private:
	std::random_device rd;
	std::mt19937 random;

	//references
	Player& player;
	Grid& grid;
	BulletManager& bulletMg;
	sf::RenderWindow& window;
	int& id;
	//values
	int fighterNumbers;
	int remainingFighter = 0;
	int fighterNumberPool;

	int elitefighterNumbers;
	int remainingEliteFighter = 0;
	int elitefighterNumberPool;

	std::vector<Entity*> ActiveFighter;
	std::vector<Entity*> ActiveElite;


	//Enemy pool
	Pool fighterEnemyPool;
	Pool eliteFighterEnemyPool;
};

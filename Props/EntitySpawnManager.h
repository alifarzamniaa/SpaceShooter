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
#include "Items/HealthItem.h"
#include "Items/ItemResource.h"

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
	// HealthDropRate is in percent, e.g. 20 means a 20% chance of dropping health.
	void EnemySpawnLogic(int& remainingNumber,int enemyNumber, Pool& pool, std::vector<Entity*>& list, int HealthDropRate);
	// DropRateChance is in percent, e.g. 20 means a 20% chance of dropping health.
	void HealthItemSpawnLogic(const sf::Vector2f& pos, int DropRateChance);

	sf::Vector2f GetRandomPosition();
private:
	std::random_device rd;
	std::mt19937 random;

	//references
	Player& player;
	Grid& grid;
	BulletManager& bulletMg;
	sf::RenderWindow& window;
	ItemResource itemResource;
	int& id;
	//values
	int fighterNumbers;
	int remainingFighter = 0;
	int fighterNumberPool;

	int elitefighterNumbers;
	int remainingEliteFighter = 0;
	int elitefighterNumberPool;


	int HealhItemPoolNum;


	std::vector<Entity*> ActiveFighter;
	std::vector<Entity*> ActiveElite;

	//Item Pool
	Pool HealthItemPool;
	//Enemy pool
	Pool fighterEnemyPool;
	Pool eliteFighterEnemyPool;
};

#pragma once
#include "SFML/Graphics.hpp"
#include "Pool.h"
#include "../Player.h"
#include "Projectile/BulletResource.h"
#include "Grid.h"
#include "../Enemy/Type1/Fighter.h"
#include "../Enemy/Type1/EliteFighter.h"
#include <random>
class SpawnManager
{
public:
	SpawnManager(int& id,Player& player,Grid& grid, sf::RenderWindow& window);
	void Draw();
	void Update(float delta);
	void SpawnEnemy();
	Pool& GetPlayerBulletPool();
	Pool& GetFighterBulletPool();
	Pool& GetEliteFighterBulletPool();
private:
	BulletResource bulltetResource;
	
	std::random_device rd;
	std::mt19937 random;

	//references
	Player& player;
	Grid& grid;
	sf::RenderWindow& window;
	int& id;
	//values
	int fighterNumbers;
	int remainingFighter = 0;
	int fighterNumberPool;

	int elitefighterNumbers;
	int remainingEliteFighter = 0;
	int elitefighterNumberPool;

	std::vector<Fighter*> ActiveFighter;
	std::vector<EliteFighter*> ActiveEliteFighter;
	//Bullets pool
	Pool playerBulletPool;

	Pool fighterBulletPool;
	Pool eliteFighterBulletPool;

	//Enemy pool
	Pool fighterEnemyPool;
	Pool eliteFighterEnemyPool;
};

#include "EntitySpawnManager.h"
#include <iostream>

EntitySpawnManager::EntitySpawnManager(int& id, Player& player, Grid& grid, sf::RenderWindow& window, BulletManager& bulletMg)
	:
	player(player),
	grid(grid),
	window(window),
	id(id),
	bulletMg(bulletMg),
	fighterNumberPool(20),
	fighterEnemyPool(fighterNumberPool),
	elitefighterNumberPool(15),
	eliteFighterEnemyPool(elitefighterNumberPool),
	random(rd())
{
	
	fighterNumbers = 5;
	elitefighterNumbers = 2;

	std::uniform_real_distribution<float> fighterPosRandY(70.f,500.f);
	std::uniform_real_distribution<float> fighterPosRandX(70.f,600.f);
	std::uniform_real_distribution<float> FighterRoamDuration(5.f,7.f);


	for(int i = 0; i < fighterNumberPool;i++)
	{
		RandomInfo info;
		info.initPos = { fighterPosRandX(random),-fighterPosRandY(random) };
		info.destinationPos = { fighterPosRandX(random),fighterPosRandY(random)};
		info.RoamDuration = FighterRoamDuration(random);
		fighterEnemyPool.AddEntity(std::make_unique<Fighter>(id++, info,window,player, bulletMg.GetFighterBulletPool(), grid));
	}
	for (int i = 0; i < elitefighterNumberPool; i++)
	{
		RandomInfo info;
		info.initPos = { fighterPosRandX(random),-fighterPosRandY(random) };
		info.destinationPos = { fighterPosRandX(random),fighterPosRandY(random) };
		info.RoamDuration = FighterRoamDuration(random);
		eliteFighterEnemyPool.AddEntity(std::make_unique<EliteFighter>(id++, info, window, player, bulletMg.GetEliteFighterBulletPool(), grid));
	}
	
}
void EntitySpawnManager::Draw()
{
	
	DrawPools(fighterEnemyPool);
	DrawPools(eliteFighterEnemyPool);

}
void EntitySpawnManager::Update(float delta)
{
	SpawnEnemy();

	UpdatePools(fighterEnemyPool,delta);
	UpdatePools(eliteFighterEnemyPool,delta);

}

void EntitySpawnManager::SpawnEnemy()
{
	SpawnLogic(remainingEliteFighter, elitefighterNumbers,eliteFighterEnemyPool,ActiveElite);
	SpawnLogic(remainingFighter,fighterNumbers,fighterEnemyPool, ActiveFighter);
}

void EntitySpawnManager::DrawPools(Pool& pool)
{
	for (auto& e : pool.GetActiveItem())
	{
		if (e)
		{
			e->Draw(window);
		}
	}
}

void EntitySpawnManager::UpdatePools(Pool& pool, float delta)
{
	for (auto& e : pool.GetActiveItem())
	{
		if (e)
		{
			e->Update(delta);
		}
	}
}
void EntitySpawnManager::SpawnLogic(int& remainingNumber, int enemyNumber,Pool& pool, std::vector<Entity*>& list)
{
		if (remainingNumber == 0)
		{
			remainingNumber = enemyNumber;
			for (int i = 0; i < enemyNumber; i++)
			{
				Entity* f = pool.GetFreeEntity();
				if (f)
				{
					f->SetActive(true);
					list.push_back(f);
				}else
				{
					std::cout << "there was no valid entity in the pool in EntitySpawnManager\n";
				}
			}
		}
		else
		{
			for (int i = 0; i < list.size(); i++)
			{
				if(list[i])
				{
					if (!list[i]->IsActive())
					{
						remainingNumber -= 1;
						list[i] = list.back();
						list.pop_back();
					}
				}else
				{
					std::cout << "we dont have a valid pointer in enemies list in spawn manager!\n";
				}
				
			}
		}
	
}


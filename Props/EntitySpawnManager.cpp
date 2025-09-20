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
	HealhItemPoolNum(10),
	HealthItemPool(HealhItemPoolNum),
	
	random(rd())
{
	
	fighterNumbers = 5;
	elitefighterNumbers = 2;


	std::uniform_real_distribution<float> FighterRoamDuration(5.f,7.f);


	for(int i = 0; i < fighterNumberPool;i++)
	{
		RandomInfo info;
		sf::Vector2f InitRandomPosition = GetRandomPosition();
		sf::Vector2f DestRandomPosition = GetRandomPosition();

		info.initPos = { InitRandomPosition.x,-InitRandomPosition.y };
		info.destinationPos = { DestRandomPosition.x,DestRandomPosition.y};
		info.RoamDuration = FighterRoamDuration(random);
		fighterEnemyPool.AddEntity(std::make_unique<Fighter>(id++, info,window,player, bulletMg.GetFighterBulletPool(), grid));
	}
	for (int i = 0; i < elitefighterNumberPool; i++)
	{
		RandomInfo info;
		sf::Vector2f InitRandomPosition = GetRandomPosition();
		sf::Vector2f DestRandomPosition = GetRandomPosition();
		info.initPos = { InitRandomPosition.x,-InitRandomPosition.y };
		info.destinationPos = { DestRandomPosition.x,DestRandomPosition.y };
		info.RoamDuration = FighterRoamDuration(random);
		eliteFighterEnemyPool.AddEntity(std::make_unique<EliteFighter>(id++, info, window, player, bulletMg.GetEliteFighterBulletPool(), grid));
	}
	for(int i = 0; i < HealhItemPoolNum;i++)
	{
		HealthItemPool.AddEntity(std::make_unique<HealthItem>(itemResource.HealthTexture,grid,id++));
	}
	
}
void EntitySpawnManager::Draw()
{
	
	DrawPools(fighterEnemyPool);
	DrawPools(eliteFighterEnemyPool);
	DrawPools(HealthItemPool);

}
void EntitySpawnManager::Update(float delta)
{
	SpawnEnemy();


	UpdatePools(fighterEnemyPool,delta);
	UpdatePools(eliteFighterEnemyPool,delta);
	UpdatePools(HealthItemPool,delta);

}

void EntitySpawnManager::SpawnEnemy()
{
	//Elite Fighter Spawn
	EnemySpawnLogic(remainingEliteFighter, elitefighterNumbers,eliteFighterEnemyPool,ActiveElite,15);
	//Figther Spawn
	EnemySpawnLogic(remainingFighter,fighterNumbers,fighterEnemyPool, ActiveFighter,5);
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
void EntitySpawnManager::EnemySpawnLogic(int& remainingNumber, int enemyNumber,Pool& pool, std::vector<Entity*>& list,int HealthDropRate)
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
						HealthItemSpawnLogic(list[i]->GetPosition(),HealthDropRate);
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

void EntitySpawnManager::HealthItemSpawnLogic(const sf::Vector2f& pos,int DropRateChance)
{
		std::uniform_int_distribution<int> Chance(0,100);
		int c = Chance(random);
		if(c < DropRateChance)
		{
			std::cout << "DROPED at c : " << c << "\n";
			Entity* h = HealthItemPool.GetFreeEntity();
			if(h)
			{
				h->SetActive(true);
				h->SetPosition(pos.x,pos.y);
			}
		}
}

sf::Vector2f EntitySpawnManager::GetRandomPosition()
{
	std::uniform_real_distribution<float> PosX(70.f, 600.f);
	std::uniform_real_distribution<float> PosY(70.f, 500.f);

	return sf::Vector2f(PosX(random),PosY(random));
}


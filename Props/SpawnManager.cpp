#include "SpawnManager.h"
SpawnManager::SpawnManager(int& id,Player& player, Grid& grid, sf::RenderWindow& window)
	:
	player(player),
	grid(grid),
	window(window),
	id(id),
	fighterNumberPool(20),
	fighterEnemyPool(fighterNumberPool),
	elitefighterNumberPool(15),
	eliteFighterEnemyPool(elitefighterNumberPool),
	random(rd())
{
	for (int i = 0; i < playerBulletPool.GetSize(); i++)
	{
		playerBulletPool.AddEntity(
			std::make_unique<Bullets>(id++, 16, 16, bulltetResource.bPlayerBulletTex, bulltetResource.bplayerAnimation, sf::IntRect({ 0,0 }, { 9,12 }), 800.f, window.getSize().y, Type::playerBullet, Type::player, grid)
		);
	}
	for (int i = 0; i < fighterBulletPool.GetSize(); i++)
	{
		fighterBulletPool.AddEntity(
			std::make_unique<Bullets>(id++, 16, 16, bulltetResource.bFighterBulletTex, bulltetResource.bfighterAnimation, sf::IntRect({ 0,0 }, { 8,16 }), 800.f, window.getSize().y, Type::enemyBullet, Type::enemy, grid)
		);
	}
	for (int i = 0; i < eliteFighterBulletPool.GetSize(); i++)
	{
		eliteFighterBulletPool.AddEntity(
			std::make_unique<Bullets>(id++, 22, 64, bulltetResource.bEliteFighterBulletTex, bulltetResource.bEliteFighterAnimation, sf::IntRect({ 0,0 }, { 11,32 }), 800.f, window.getSize().y, Type::enemyBullet, Type::enemy, grid)
		);
	}
	fighterNumbers = 6;
	elitefighterNumbers = 1;

	std::uniform_real_distribution<float> fighterPosRandY(70.f,500.f);
	std::uniform_real_distribution<float> fighterPosRandX(70.f,600.f);
	std::uniform_real_distribution<float> FighterRoamDuration(2.f,7.f);
	for(int i = 0; i < fighterNumberPool;i++)
	{
		RandomInfo info;
		info.initPos = { fighterPosRandX(random),-fighterPosRandY(random) };
		info.destinationPos = { fighterPosRandX(random),fighterPosRandY(random)};
		info.RoamDuration = FighterRoamDuration(random);
		fighterEnemyPool.AddEntity(std::make_unique<Fighter>(id++, info,window,player,GetFighterBulletPool(), grid));
	}
	for (int i = 0; i < elitefighterNumberPool; i++)
	{
		RandomInfo info;
		info.initPos = { fighterPosRandX(random),-fighterPosRandY(random) };
		info.destinationPos = { fighterPosRandX(random),fighterPosRandY(random) };
		info.RoamDuration = FighterRoamDuration(random);
		eliteFighterEnemyPool.AddEntity(std::make_unique<EliteFighter>(id++, info, window, player, GetEliteFighterBulletPool(), grid));
	}
	
}
void SpawnManager::Draw()
{
	/*for (auto& e : fighterEnemyPool.GetActiveItem())
	{
		if (e)
		{
			e->Draw(window);
		}
	}*/
	for (auto& e : eliteFighterEnemyPool.GetActiveItem())
	{
		if (e)
		{
			e->Draw(window);
		}
	}
	for (auto& e : eliteFighterBulletPool.GetActiveItem())
	{
		if (e)
		{
			e->Draw(window);
		}
	}
	for (auto& e : playerBulletPool.GetActiveItem())
	{
		if (e)
		{
			e->Draw(window);
		}
	}
	for (auto& e : fighterBulletPool.GetActiveItem())
	{
		if (e)
		{
			e->Draw(window);
		}
	}
}
void SpawnManager::Update(float delta)
{
	SpawnEnemy();
	/*for (auto& e : fighterEnemyPool.GetActiveItem())
	{
		if (e)
		{
			e->Update(delta);
		}
	}*/
	for (auto& e : eliteFighterEnemyPool.GetActiveItem())
	{
		if (e)
		{
			e->Update(delta);
		}
	}
	for (auto& e : eliteFighterBulletPool.GetActiveItem())
	{
		if (e)
		{
			e->Update(delta);
		}
	}
	for (auto& e : playerBulletPool.GetActiveItem())
	{
		if (e)
		{
			e->Update(delta);
		}
	}
	for (auto& e : fighterBulletPool.GetActiveItem())
	{
		if (e)
		{
			e->Update(delta);
		}
	}
}

void SpawnManager::SpawnEnemy()
{
	if(remainingFighter == 0)
	{
		remainingFighter = fighterNumbers;
		for (int i = 0; i < fighterNumbers; i++)
		{
			Fighter* f = dynamic_cast<Fighter*>(fighterEnemyPool.GetFreeEntity());
			if (f)
			{
				f->SetActive(true);
				ActiveFighter.push_back(f);
			}
		}
	}
	else
	{
		for (int i = 0;i < ActiveFighter.size(); i++)
		{
			if (!ActiveFighter[i]->IsActive())
			{
				remainingFighter -= 1;
				ActiveFighter[i] = ActiveFighter.back();
				ActiveFighter.pop_back();
			}
		}
	}
	if (remainingEliteFighter == 0)
	{
		remainingEliteFighter = elitefighterNumbers;
		for (int i = 0; i < elitefighterNumbers; i++)
		{
			EliteFighter* f = dynamic_cast<EliteFighter*>(eliteFighterEnemyPool.GetFreeEntity());
			if (f)
			{
				f->SetActive(true);
				ActiveEliteFighter.push_back(f);
			}
		}
	}
	else
	{
		for (int i = 0; i < ActiveEliteFighter.size(); i++)
		{
			if (!ActiveEliteFighter[i]->IsActive())
			{
				remainingEliteFighter -= 1;
				ActiveEliteFighter[i] = ActiveEliteFighter.back();
				ActiveEliteFighter.pop_back();
			}
		}
	}
}

Pool& SpawnManager::GetPlayerBulletPool()
{
	return playerBulletPool;
}

Pool& SpawnManager::GetFighterBulletPool()
{
	return fighterBulletPool;
}

Pool& SpawnManager::GetEliteFighterBulletPool()
{
	return eliteFighterBulletPool;
}

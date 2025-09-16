#include "BulletManager.h"

BulletManager::BulletManager(int& id, Grid& grid, sf::RenderWindow& window)
:
	id(id),
	grid(grid),
	window(window)
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
			std::make_unique<Bullets>(id++, 16, 16, bulltetResource.bFighterBulletTex, bulltetResource.bfighterAnimation, sf::IntRect({ 0,0 }, { 8,16 }), 800.f, window.getSize().y, Type::fighterBullet, Type::enemy, grid)
		);
	}
	for (int i = 0; i < eliteFighterBulletPool.GetSize(); i++)
	{
		eliteFighterBulletPool.AddEntity(
			std::make_unique<Bullets>(id++, 22, 64, bulltetResource.bEliteFighterBulletTex, bulltetResource.bEliteFighterAnimation, sf::IntRect({ 0,0 }, { 11,32 }), 800.f, window.getSize().y, Type::eliteFighterBullet, Type::enemy, grid)
		);
	}
}
void BulletManager::Draw()
{
	DrawPools(fighterBulletPool);
	DrawPools(eliteFighterBulletPool);
	DrawPools(playerBulletPool);

}
void BulletManager::Update(float delta)
{
	UpdatePools(fighterBulletPool, delta);
	UpdatePools(eliteFighterBulletPool, delta);
	UpdatePools(playerBulletPool, delta);
}
Pool& BulletManager::GetPlayerBulletPool()
{
	return playerBulletPool;
}

Pool& BulletManager::GetFighterBulletPool()
{
	return fighterBulletPool;
}

Pool& BulletManager::GetEliteFighterBulletPool()
{
	return eliteFighterBulletPool;
}
void BulletManager::DrawPools(Pool& pool)
{
	for (auto& e : pool.GetActiveItem())
	{
		if (e)
		{
			e->Draw(window);
		}
	}
}

void BulletManager::UpdatePools(Pool& pool, float delta)
{
	for (auto& e : pool.GetActiveItem())
	{
		if (e)
		{
			e->Update(delta);
		}
	}
}


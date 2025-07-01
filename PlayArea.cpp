#include "PlayArea.h"
#include <iostream>
PlayArea::PlayArea(int PlayerBulletSize, sf::RenderWindow& window)
	:
	window(window),
	playerBulletPool(PlayerBulletSize),
	fighterBulletPool(100),
	player({600.f,600.f}),
	bg(window,200.f),
	f1({200.f,200.f},window,player,fighterBulletPool),
	grid(64,64,window)
{
	for(int i = 0; i < playerBulletPool.GetSize();i++)
	{
		playerBulletPool.AddEntity(
			std::make_unique<Bullets>(15,15,player.GetBulletTex(),player.GetBulletAnim(), sf::IntRect({ 0,0 }, { 9,12 }),800.f,window.getSize().y,"Player")
		);
	}
	for(int i = 0; i < fighterBulletPool.GetSize();i++)
	{
		fighterBulletPool.AddEntity(
			std::make_unique<Bullets>(15,15,f1.GetBulletTex(),f1.GetBulletAnim(), sf::IntRect({ 0,0 }, { 8,16 }),800.f,window.getSize().y,"Enemy")
		);
	}

}

void PlayArea::Draw()
{
	bg.Draw(window);
	player.Draw(window);
	for (auto& e : playerBulletPool.GetActiveItem())
	{
		if (e)
			e->Draw(window);
	}
	for (auto& f : fighterBulletPool.GetActiveItem())
	{
		if (f)
			f->Draw(window);
	}
	f1.Draw(window);
}

void PlayArea::Update(float delta)
{
	Timer += delta;
	if(Timer >= 1.f)
	{
		grid.ResetCollisionCheck();
		Timer = 0.0f;
	}
	player.Movement(delta, { 0,(float)window.getSize().x }, { 0,(float)window.getSize().y });
	player.Update(delta);
	player.OnHit(grid);
	grid.AddToGrid(&player);
	bg.Update(delta,window);
	f1.Update(delta);
	grid.AddToGrid(&f1);
	// updating the active bullets
	for(auto& e : playerBulletPool.GetActiveItem())
	{
		if(e)
		{
			e->Update(delta);
			grid.AddToGrid(e);
		}
	}
	for (auto& e : fighterBulletPool.GetActiveItem())
	{
		if (e)
		{
			e->Update(delta);
			grid.AddToGrid(e);
		}
	}
}

void PlayArea::InputHandler(float delta, std::optional<sf::Event> e)
{
	// handling events like pressed, released ... 
	player.Actions(delta, playerBulletPool,e);
}

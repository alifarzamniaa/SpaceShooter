#include "PlayArea.h"
#include <iostream>
PlayArea::PlayArea(int PlayerBulletSize, sf::RenderWindow& window)
	:
	window(window),
	playerBulletPool(PlayerBulletSize),
	player({600.f,600.f}),
	bg(window,200.f),
	f1({200.f,100.f},window,player)
{
	for(int i = 0; i < playerBulletPool.GetSize();i++)
	{
		playerBulletPool.AddEntity(
			std::make_unique<Bullets>(15,15,player.GetBulletTex(),player.GetBulletAnim(), sf::IntRect({ 0,0 }, { 9,12 }),800.f)
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
	f1.Draw(window);
}

void PlayArea::Update(float delta)
{
	player.Movement(delta, { 0,(float)window.getSize().x }, { 0,(float)window.getSize().y });
	player.Update(delta);
	bg.Update(delta,window);
	f1.Update(delta);
	// updating the active bullets
	for(auto& e : playerBulletPool.GetActiveItem())
	{
		if(e)
			e->Update(delta);
	}
}

void PlayArea::InputHandler(float delta, std::optional<sf::Event> e)
{
	// handling events like pressed, released ... 
	player.Actions(delta, playerBulletPool,e);
}

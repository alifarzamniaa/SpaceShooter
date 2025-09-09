#include "PlayArea.h"
#include <iostream>
PlayArea::PlayArea(int PlayerBulletSize, sf::RenderWindow& window)
	:
	window(window),
	playerBulletPool(PlayerBulletSize),
	fighterBulletPool(100),
	grid(32,32,window),
	bg(window,100.f),
	player(id++,{600.f,600.f},grid,UI),
	f1(id++,{200.f,200.f},window,player,fighterBulletPool,grid),
	UI(window,player.GetHealth())
{
	if(!GameMusic.openFromFile("SoundEffects/GameMusic.wav"))
	{
		std::cout << "Cant Load Game Music!!\n";
	}
	for(int i = 0; i < playerBulletPool.GetSize();i++)
	{
		playerBulletPool.AddEntity(
			std::make_unique<Bullets>(id++,16,16,player.GetBulletTex(),player.GetBulletAnim(), sf::IntRect({ 0,0 }, { 9,12 }),800.f,window.getSize().y,Type::playerBullet,Type::player, grid)
		);
	}
	for(int i = 0; i < fighterBulletPool.GetSize();i++)
	{
		fighterBulletPool.AddEntity(
			std::make_unique<Bullets>(id++,16,16,f1.GetBulletTex(),f1.GetBulletAnim(), sf::IntRect({ 0,0 }, { 8,16 }),800.f,window.getSize().y, Type::enemyBullet, Type::enemy, grid)
		);
	}
	GameMusic.setLooping(true);
	GameMusic.setVolume(40.f);
	GameMusic.setPlayingOffset(sf::seconds(0.5f));
	GameMusic.setLoopPoints({sf::seconds(0.5f),sf::seconds(367.2f)});
	GameMusic.play();
}

void PlayArea::Draw()
{
	bg.Draw(window);
	UI.Draw();
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
	
	bg.Update(delta,window);
	player.Update(delta);
	player.Movement(delta, { 0,(float)window.getSize().x }, { 0,(float)window.getSize().y });
	f1.Update(delta);
	// updating the active bullets
	for(auto& e : playerBulletPool.GetActiveItem())
	{
		if(e)
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

void PlayArea::InputHandler(float delta, std::optional<sf::Event> e)
{
	// handling events like pressed, released ... 
	player.Actions(delta, playerBulletPool,e);
}

#include "GameManager.h"
#include <iostream>
GameManager::GameManager(sf::RenderWindow& window)
	:
	window(window),
	grid(32,32,window),
	bg(window,50.f),
	player(id++,{600.f,600.f},grid,UI),
	bulletManager(id, grid, window),
	spawnManager(id,player,grid,window,bulletManager),
	UI(window,player.GetHealth())
{
	if(!GameMusic.openFromFile("SoundEffects/GameMusic.wav"))
	{
		std::cout << "Cant Load Game Music!!\n";
	}
	GameMusic.setLooping(true);
	GameMusic.setVolume(40.f);
	GameMusic.setPlayingOffset(sf::seconds(0.5f));
	GameMusic.setLoopPoints({sf::seconds(0.5f),sf::seconds(367.2f)});
	GameMusic.play();
}

void GameManager::Draw()
{
	bg.Draw(window);
	UI.Draw();
	player.Draw(window);
	bulletManager.Draw();
	spawnManager.Draw();
}
void GameManager::Update(float delta)
{
	
	bg.Update(delta,window);
	player.Update(delta);
	player.Movement(delta, { 0,(float)window.getSize().x }, { 0,(float)window.getSize().y });
	bulletManager.Update(delta);
	spawnManager.Update(delta);
}

void GameManager::InputHandler(float delta, std::optional<sf::Event> e)
{
	// handling events like pressed, released ... 
	player.Actions(delta, bulletManager.GetPlayerBulletPool(), e);
}

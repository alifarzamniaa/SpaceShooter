#include "PlayArea.h"
#include <iostream>
PlayArea::PlayArea(sf::RenderWindow& window)
	:
	window(window),
	grid(32,32,window),
	bg(window,50.f),
	player(id++,{600.f,600.f},grid,UI),
	spawnManager(id,player,grid,window),
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

void PlayArea::Draw()
{
	bg.Draw(window);
	UI.Draw();
	player.Draw(window);
	spawnManager.Draw();
}
void PlayArea::Update(float delta)
{
	
	bg.Update(delta,window);
	player.Update(delta);
	player.Movement(delta, { 0,(float)window.getSize().x }, { 0,(float)window.getSize().y });
	spawnManager.Update(delta);
}

void PlayArea::InputHandler(float delta, std::optional<sf::Event> e)
{
	// handling events like pressed, released ... 
	player.Actions(delta, spawnManager.GetPlayerBulletPool(), e);
}

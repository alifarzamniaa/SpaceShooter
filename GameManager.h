#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Props/Pool.h"
#include "Props/Projectile/Bullets.h"
#include "Props/Projectile/BulletManager.h"
#include "background.h"
#include "Enemy/Type1/Fighter.h"
#include "Props/Grid.h"
#include "UI/UIManager.h"
#include "Props/EntitySpawnManager.h"

class GameManager
{
public:
	GameManager(sf::RenderWindow& window);
	void Draw();
	void Update(float delta);
	void InputHandler(float delta,std::optional<sf::Event> e);
private:
	int id = 0;
	sf::RenderWindow& window;
	Grid grid;
	Player player;
	Background bg;
	BulletManager bulletManager;
	EntitySpawnManager spawnManager;
	UIManager UI;
	sf::Music GameMusic;
	float Timer = 0.0f;
};


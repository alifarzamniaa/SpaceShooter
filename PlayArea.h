#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Props/Pool.h"
#include "Props/Bullets.h"
#include "background.h"
#include "Enemy/Type1/Fighter.h"
#include "Props/Grid.h"
class PlayArea
{
public:
	PlayArea(int PlayerBulletSize, sf::RenderWindow& window);
	void Draw();
	void Update(float delta);
	void InputHandler(float delta,std::optional<sf::Event> e);
private:
	int id = 0;
	sf::RenderWindow& window;
	Grid grid;
	Player player;
	Background bg;
	Pool playerBulletPool;
	Pool fighterBulletPool;
	Fighter f1;

	float Timer = 0.0f;
};


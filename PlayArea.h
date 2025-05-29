#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Props/Pool.h"
#include "Props/Bullets.h"
#include "background.h"
#include "Enemy/Fighter.h"
class PlayArea
{
public:
	PlayArea(int PlayerBulletSize, sf::RenderWindow& window);
	void Draw();
	void Update(float delta);
	void InputHandler(float delta,std::optional<sf::Event> e);
private:
	sf::RenderWindow& window;
	Player player;
	Background bg;
	Pool playerBulletPool;
	Fighter f1;
};


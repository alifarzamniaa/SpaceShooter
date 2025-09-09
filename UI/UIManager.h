#pragma once
#include "PlayerHealth.h"
#include "SFML/Graphics.hpp"
class UIManager
{
public:
	UIManager(sf::RenderWindow& window,float PlayerInitHealth);
	void Draw();
	void PlayerHealthChange(float Health);
private:
	sf::RenderWindow& window;
	PlayerHealth pHealth;
};
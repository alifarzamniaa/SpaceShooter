#pragma once
#include "SFML/Graphics.hpp"
#include "../../Animation.h"
class BulletResource
{
public:
	BulletResource();

	Animation bfighterAnimation;
	Animation bplayerAnimation;
	Animation bEliteFighterAnimation;

	sf::Texture bFighterBulletTex;
	sf::Texture bPlayerBulletTex;
	sf::Texture bEliteFighterBulletTex;
};
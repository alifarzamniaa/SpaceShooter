#include "BulletResource.h"
#include <iostream>
BulletResource::BulletResource()
	:
	bfighterAnimation(8, 16, 4, 0.1f),
	bplayerAnimation(9, 12, 8, 0.09f),
	bEliteFighterAnimation(11, 32, 3, 0.09f)
{
	if (!bFighterBulletTex.loadFromFile("Images/Bullets/Enemy/Type1/FighterBullet.png"))
	{
		std::cout << "FAILED TO LOAD FIGHTER BULLET TEXTURE!!!\n";
	}
	if (!bEliteFighterBulletTex.loadFromFile("Images/Bullets/Enemy/Type1/EliteFighterBullet.png"))
	{
		std::cout << "FAILED TO LOAD FIGHTER BULLET TEXTURE!!!\n";
	}
	if (!bPlayerBulletTex.loadFromFile("Images/Bullets/PlayerBullet.png"))
	{
		std::cout << "FAILED TO LOAD PLAYER BULLET TEXTURE!!!\n";
	}

}

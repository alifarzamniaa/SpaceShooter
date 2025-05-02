#include "Player.h"

Player::Player(const sf::Vector2f& pos)
	:
	sp(pos,BaseImgPath,EngineImgPath,ShieldImgPath)
{
	sp.SetSize({ PlayerShipSize,PlayerShipSize });
	sp.UpdateEngineTexRect(sf::IntRect({0, 0},{64,64}));
	sp.UpdateShieldTexRect(sf::IntRect({0, 0},{64,64}));
}

void Player::Draw(sf::RenderWindow& window)
{
	sp.Draw(window);
}

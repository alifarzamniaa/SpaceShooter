#include "Player.h"

Player::Player(const sf::Vector2f& pos)
	:
	sp(pos,BaseImgPath,EngineImgPath,ShieldImgPath)
{
	sp.SetSize({ playerShipSize,playerShipSize });
	sp.UpdateBaseTexRect(sf::IntRect({0, 0},{64,64}));
	sp.UpdateEngineTexRect(sf::IntRect({0, 0},{64,64}));
	sp.UpdateShieldTexRect(sf::IntRect({0, 0},{64,64}));
}

void Player::Draw(sf::RenderWindow& window)
{
	sp.Draw(window);
}

void Player::Movement(float delta,const sf::Vector2f& leftRightBound, const sf::Vector2f& topBottomBound)
{
	sf::Vector2f dir = {0,0};
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		dir.y = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		dir.y = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		dir.x = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		dir.x = -1;
	}
	if(dir.length() > 1)
		dir = dir.normalized();

	sp.SetPosition(sp.GetPosition() + (dir * speed * delta));
	WallCollision(leftRightBound,topBottomBound);
}

void Player::WallCollision(const sf::Vector2f& leftRightBound, const sf::Vector2f& TopBottomBound)
{
	float left = leftRightBound.x;
	float right = leftRightBound.y;
	float top = TopBottomBound.x;
	float bottom = TopBottomBound.y;

	float meshRightSide = (sp.GetPosition().x + sp.GetSize().x) - verticalPadding;
	float meshLeftSide = sp.GetPosition().x + verticalPadding;
	float meshTopSide = sp.GetPosition().y + horizontalPadding;
	float meshBottomSide = (sp.GetPosition().y + sp.GetSize().y) - horizontalPadding;
	if(meshRightSide > right)
	{
		sp.SetPosition({ right - sp.GetSize().x + verticalPadding, sp.GetPosition().y });// keep the y pos same and fix it to right
	}
	if (meshLeftSide < left)
	{
		sp.SetPosition({ left - verticalPadding , sp.GetPosition().y}); // keep the y pos same and fix it to left
	}
	if (meshBottomSide > bottom)
	{
		sp.SetPosition({sp.GetPosition().x , bottom - sp.GetSize().y + horizontalPadding }); // keep the x pos same and fix it to bottom
	}
	if (meshTopSide < top)
	{
		sp.SetPosition({sp.GetPosition().x, top - horizontalPadding }); // keep the x pos same and fix it to top
	}
}

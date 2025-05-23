#include "Player.h"
#include <iostream>

Player::Player(const sf::Vector2f& pos)
	:
	sp(pos,BaseImgPath,EngineImgPath,ShieldImgPath),
	EngineAnim(64,64,8,0.1f),
	ShieldAnim(64,64,10,0.09f),
	BulletAnim(9,12,8,0.09f),
	FiringAnim(64,64,9,0.03f)
{
	if(!BulletTex.loadFromFile(BulletImgPath))
	{
		std::cout << "FAILED TO LOAD BULLET TEXTURE!!!\n";
	}
	sp.SetSize({ playerShipSize,playerShipSize });
	sp.UpdateBaseTexRect(sf::IntRect({0, 0},{64,64}));
	sp.UpdateEngineTexRect(sf::IntRect({0, 0},{64,64}));
	sp.UpdateShieldTexRect(sf::IntRect({0, 0},{64,64}));

	
}

void Player::Draw(sf::RenderWindow& window)
{
	sp.Draw(window);
}

void Player::Update(float delta)
{
	EngineAnim.Update(delta);
	sp.UpdateEngineTexRect(EngineAnim.GetCurrentFrame());
	if (sp.GetShieldState())
	{
		ShieldAnim.Update(delta);
		sp.UpdateShieldTexRect(ShieldAnim.GetCurrentFrame());
	}
	if (IsFiring)
	{
		FiringAnim.Update(delta);
		sp.UpdateBaseTexRect(FiringAnim.GetCurrentFrame());
		if(FiringAnim.IsAnimFinished())
		{
			IsFiring = false;
		}
	}
}

sf::Vector2f Player::GetPosition() const
{
	return sp.GetPosition();
}

sf::Vector2f Player::GetSize() const
{
	return sp.GetSize();
}

void Player::SetPosition(float x, float y)
{
	sp.SetPosition({x,y});
}

void Player::SetSize(float width, float height)
{
	sp.SetSize({ width,height });
}

bool Player::IsActive() const
{
	return ActiveState;
}

void Player::SetActive(bool in_state)
{
	ActiveState = in_state;
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
	// this is fix for diagonal movement which caused fast movement
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

void Player::Actions(float delta, Pool& bulletPool,std::optional<sf::Event> e)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
	{
		sp.SetShieldState(true);
	}
	// if mouse is pressed and it is left mouse button
	if (const auto* mouseButtonPressed = e->getIf<sf::Event::MouseButtonPressed>())
	{
		IsFiring = true;
		if (mouseButtonPressed->button == sf::Mouse::Button::Left)
		{
			Bullets* firstBullet = dynamic_cast<Bullets*>(bulletPool.GetFreeEntity());
			if (firstBullet)
			{
				sf::Vector2f FirstMuzzleLocation = GetPosition() + LBulletSocket;
				firstBullet->SetPosition(FirstMuzzleLocation.x, FirstMuzzleLocation.y);
				firstBullet->SetActive(true);
			}
			Bullets* secondBullet = dynamic_cast<Bullets*>(bulletPool.GetFreeEntity());
			if (secondBullet)
			{
				sf::Vector2f SecondMuzzleLocation = GetPosition() + RBulletSocket;
				secondBullet->SetPosition(SecondMuzzleLocation.x, SecondMuzzleLocation.y);
				secondBullet->SetActive(true);
			}
		}
	}
}


sf::Texture& Player::GetBulletTex()
{
	return BulletTex;
}

Animation Player::GetBulletAnim()
{
	return BulletAnim;
}

#include "Player.h"
#include <iostream>

Player::Player(const sf::Vector2f& pos)
	:
	sp(pos,BaseImgPath,EngineImgPath,ShieldImgPath,DestructionImgPath),
	EngineAnim(64,64,8,0.1f),
	ShieldAnim(64,64,10,0.09f),
	BulletAnim(9,12,8,0.09f),
	FiringAnim(64,64,9,0.03f),
	DestructionAnim(64,64,8,0.15f)
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
	if(IsActive())
		sp.Draw(window);
}

void Player::Update(float delta)
{
	if(IsActive())
	{
		//Checks if the health reaches 0 and destroy the ship
		DestructionEvent(delta);
		if(!IsDestroyed())
		{
			EngineAnim.Update(delta);
			sp.UpdateEngineTexRect(EngineAnim.GetCurrentFrame());
			if (sp.GetShieldState())
			{
				ShieldAnim.Update(delta);
				sp.UpdateShieldTexRect(ShieldAnim.GetCurrentFrame());
			}
			if (IsFiring())
			{
				FiringAnim.Update(delta);
				sp.UpdateBaseTexRect(FiringAnim.GetCurrentFrame());
				if (FiringAnim.IsAnimFinished())
				{
					SetFiringState(false);
				}
			}
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

void Player::SetDestroyedState(bool in_State)
{
	Destroyed = in_State;
}

bool Player::IsDestroyed() const
{
	return Destroyed;
}

void Player::OnHit(Grid& grid)
{	
	if(grid.IsEntityCollides(*this))
	{
		health -= 10;
		std::cout << "health : " << health << '\n';
	}
}

void Player::SetFiringState(bool in_State)
{
	Firing = in_State;
}

bool Player::IsFiring() const
{
	return Firing;
}

float Player::GetSpeed() const
{
	return speed;
}

int Player::GetHealth() const
{
	return health;
}

void Player::SetSpeed(float in_val)
{
	speed = in_val;
}

void Player::SetHealth(int in_val)
{
	health = in_val;
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

	float meshRightSide = (sp.GetPosition().x + (sp.GetSize().x / 2)) - verticalPadding;
	float meshLeftSide = sp.GetPosition().x - (sp.GetSize().x / 2) + verticalPadding;
	float meshTopSide = (sp.GetPosition().y - (sp.GetSize().y / 2)) + horizontalPadding;
	float meshBottomSide = (sp.GetPosition().y + (sp.GetSize().y)) - horizontalPadding;
	if(meshRightSide > right)
	{
		sp.SetPosition({ right - (sp.GetSize().x / 2) + verticalPadding, sp.GetPosition().y });// keep the y pos same and fix it to right
	}
	if (meshLeftSide < left)
	{
		sp.SetPosition({ left + (sp.GetSize().x / 2) - verticalPadding , sp.GetPosition().y}); // keep the y pos same and fix it to left
	}
	if (meshBottomSide > bottom)
	{
		sp.SetPosition({sp.GetPosition().x , bottom - (sp.GetSize().y ) + horizontalPadding }); // keep the x pos same and fix it to bottom
	}
	if (meshTopSide < top)
	{
		sp.SetPosition({sp.GetPosition().x, top + (sp.GetSize().y / 2) - horizontalPadding }); // keep the x pos same and fix it to top
	}
}

void Player::DestructionEvent(float delta)
{
	if (health <= 0 && !IsDestroyed())
	{
		sp.ActiveDestruction();
		SetDestroyedState(true);
	}
	if (IsDestroyed())
	{
		sp.SetEngineState(false);
		DestructionAnim.Update(delta);
		sp.UpdateBaseTexRect(DestructionAnim.GetCurrentFrame());
		if (DestructionAnim.IsAnimFinished())
		{
			SetActive(false);
		}
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
		SetFiringState(true);
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

std::vector<sf::Vector2i>& Player::GetLastOccupied()
{
	return LastOccupied;
}

void Player::SetOccupied(std::vector<sf::Vector2i>& occupiedSpace)
{
	LastOccupied = occupiedSpace;
}

std::string Player::GetTag() const
{
	return Tag;
}

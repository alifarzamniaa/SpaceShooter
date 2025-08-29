#include "Bullets.h"
#include <iostream>

Bullets::Bullets(int id, float width, float height, const sf::Texture& bulletModel, const Animation& bulletAnim, const sf::IntRect& TexRect, float fireSpeed, int windowHeight,const Type& Bullettype, const Type& ShooterType, Grid& grid)
	:
	bulletAnim(bulletAnim),
	speed(fireSpeed),
	windowHeight(windowHeight),
	type(Bullettype),
	ShootersType(ShooterType),
	grid(grid)
{
	bullet.setSize({width,height});
	bullet.setTexture(&bulletModel);
	bullet.setTextureRect(TexRect);
	bullet.setOrigin(bullet.getSize() / 2.f);
	Info.id = id;
}

void Bullets::Update(float delta)
{
	//disabled when out of screen
	if(IsActive())
	{
		bulletAnim.Update(delta);
		bullet.setTextureRect(bulletAnim.GetCurrentFrame());
		Fire(delta);
		Info.Position = GetPosition();
		Info.Size = GetSize() / 2.f;
		Info.EntityType = GetType();
		grid.AddToGrid(Info);
		
		if (GetPosition().y < 0 || GetPosition().y >= windowHeight)
		{
			SetActive(false);
			grid.RemoveFromGrid(Info);
			return;
		}
		if (IsDestroyed())
		{
			SetActive(false);
			grid.RemoveFromGrid(Info);
			return;
		}
		OnHit();
	}
		
}

void Bullets::Draw(sf::RenderWindow& window)
{
	if(ActiveState)
	{
		window.draw(bullet);
	}
}
void Bullets::Fire(float delta)
{
	//negative shoots upward , positive shoot downward
	float vel = Direction ? speed * delta : -speed * delta;
	bullet.move(sf::Vector2f{ 0,vel });
}
void Bullets::SetSize(float width, float height)
{
	bullet.setSize(sf::Vector2f{width,height});
}

void Bullets::SetDestroyedState(bool in_State)
{
	Destroyed = in_State;
}

bool Bullets::IsDestroyed() const
{
	return Destroyed;
}

void Bullets::SetPosition(float x,float y)
{
	bullet.setPosition({x,y});
}

void Bullets::SetActive(bool in_state)
{
	ActiveState = in_state;
	if(ActiveState)
		SetDestroyedState(false);
}

bool Bullets::GetDirection() const
{
	return Direction;
}

void Bullets::SetDirection(bool in_val)
{
	if(Direction != in_val)
		bullet.setRotation(sf::Angle(sf::degrees(180.f)));

	Direction = in_val;
}
void Bullets::OnHit()
{
	bool ShouldDestroy = false;
	if(grid.IsEntityCollides(Info) && !IsDestroyed())
	{
		Info.Position = GetPosition();
		auto Entities = grid.GetCollidedEntites(Info);
		for(const auto& e : Entities)
		{
			//its not a bullet && its not damaging the shooter(player bullet doesn't damage the player)
			if(e.EntityType != Type::playerBullet && e.EntityType != Type::enemyBullet)
			{
				if(ShootersType != e.EntityType)
				{
					SetDestroyedState(true);
				}
			}
		}
	}
}
Type Bullets::GetType() const
{
	return type;
}

sf::Vector2f Bullets::GetPosition() const
{
	return bullet.getPosition();
}

sf::Vector2f Bullets::GetSize() const
{
	return bullet.getSize();
}

bool Bullets::IsActive() const
{
	return ActiveState;
}
std::vector<sf::Vector2i>& Bullets::GetLastOccupied()
{
	return LastOccupied;
}

void Bullets::SetOccupied(std::vector<sf::Vector2i>& occupiedSpace)
{
	LastOccupied = occupiedSpace;
}
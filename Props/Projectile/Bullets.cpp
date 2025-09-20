#include "Bullets.h"
#include <iostream>

Bullets::Bullets(int id, float width, float height, const sf::Texture& bulletModel, const Animation& bulletAnim, const sf::IntRect& TexRect, float fireSpeed, int windowHeight,const Type& Bullettype, const Type& ShooterType, Grid& grid)
	:
	bulletAnim(bulletAnim),
	speed(fireSpeed),
	windowHeight(windowHeight),
	type(Bullettype),
	ShootersType(ShooterType),
	grid(grid),
	FireSoundBuffer("SoundEffects/PlayerWeapon.wav"),
	FireSound(FireSoundBuffer),
	onHitParticle("Images/Particle/BulletHit.png",
				  "SoundEffects/Explosion1.wav",
				  {
					32,
					32,
					16,
					16,
					6,
					0.01f
				  })
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
		if (!IsDestroyed())
		{
			if (GetPosition().y < 0 || GetPosition().y >= windowHeight)
			{
				SetActive(false);
				grid.RemoveFromGrid(Info);
			}else
			{
				bulletAnim.Update(delta);
				bullet.setTextureRect(bulletAnim.GetCurrentFrame());
				Fire(delta);
				Info.Position = GetPosition();
				Info.Size = GetSize() / 2.f;
				Info.EntityType = GetType();
				grid.AddToGrid(Info);

				OnHit();
			}
		}else
		{
			grid.RemoveFromGrid(Info);
			DestructionEvent(delta);
		}
	}
	
		
}
void Bullets::DestructionEvent(float delta)
{
	if(!onHitParticle.IsFinished())
	{
		Info.Position = GetPosition();
		onHitParticle.Play(Info.Position, delta);
	}else
	{
		SetActive(false);
	}
}
void Bullets::Draw(sf::RenderWindow& window)
{
	if(!IsDestroyed())
	{
		window.draw(bullet);
	}
	onHitParticle.Draw(window);
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
	{
		SetDestroyedState(false);
		FireSound.play();
	}
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
	if(grid.IsEntityCollides(Info) && !IsDestroyed())
	{
		Info.Position = GetPosition();
		auto Entities = grid.GetCollidedEntites(Info);
		for(const auto& e : Entities)
		{
			//its not a bullet && its not damaging the shooter(player bullet doesn't damage the player)
			if(e.EntityType == player || e.EntityType == enemy)
			{
				if(ShootersType != e.EntityType)
				{
					onHitParticle.ActivateParticle();
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

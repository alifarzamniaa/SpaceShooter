#include "HealthItem.h"
#include <iostream>
HealthItem::HealthItem(const sf::Texture& tex, Grid& grid, int Id)
	:
	grid(grid),
	OnHitSound(OnHitSoundBuffer)
{
	if (!OnHitSoundBuffer.loadFromFile("SoundEffects/HealthUp.wav"))
	{
		std::cout << "FAILED TO LOAD Health SOUND!!!\n";
	}
	healthBox.setTexture(&tex);
	healthBox.setSize({32.f,32.f});
	healthBox.setOrigin(healthBox.getSize() / 2.f);
	ActiveState = false;
	Destroyed = false;
	speed = 400;

	Info.EntityType = type;
	Info.id = Id;
	Info.Position = healthBox.getPosition();
	Info.Size = healthBox.getSize() / 2.f;
}
void HealthItem::Update(float delta)
{
	if(IsActive())
	{	
		if(!IsDestroyed())
		{
			healthBox.setPosition({ GetPosition().x,GetPosition().y + speed * delta });
			Info.Position = healthBox.getPosition();
			grid.AddToGrid(Info);
			OnHit();
		}else
		{
			SetActive(false);
			Info.Position = healthBox.getPosition();
			grid.RemoveFromGrid(Info);
			OnHitSound.play();
		}
		
	}
}
void HealthItem::Draw(sf::RenderWindow& window)
{
	if ( IsActive() && !IsDestroyed())
	{
		window.draw(healthBox);
	}
}
void HealthItem::SetSize(float width, float height)
{
	healthBox.setSize(sf::Vector2f{ width,height });
}

void HealthItem::SetDestroyedState(bool in_State)
{
	Destroyed = in_State;
}

bool HealthItem::IsDestroyed() const
{
	return Destroyed;
}

void HealthItem::SetPosition(float x, float y)
{
	healthBox.setPosition({ x,y });
}

void HealthItem::SetActive(bool in_state)
{
	ActiveState = in_state;
	if (ActiveState)
	{
		SetDestroyedState(false);
	}
}
void HealthItem::OnHit()
{
	if (grid.IsEntityCollides(Info) && !IsDestroyed())
	{
		Info.Position = GetPosition();
		auto Entities = grid.GetCollidedEntites(Info);
		for (const auto& e : Entities)
		{
			if (e.EntityType == player)
			{
				SetDestroyedState(true);
			}
		}
	}
}
Type HealthItem::GetType() const
{
	return type;
}

sf::Vector2f HealthItem::GetPosition() const
{
	return healthBox.getPosition();
}

sf::Vector2f HealthItem::GetSize() const
{
	return healthBox.getSize();
}

bool HealthItem::IsActive() const
{
	return ActiveState;
}

float HealthItem::GetHPRestoration() const
{
    return 0.0f;
}

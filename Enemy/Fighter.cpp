#include "Fighter.h"
#include "../AI/Actions/Roam.h"
#include "../AI/Actions/MoveTo.h"
#include <math.h>

Fighter::Fighter(const sf::Vector2f& pos, sf::RenderWindow& window, Player& player)
	:
	Enemy(window,player,pos,
	{
	{64, 64, 6, 0.03f, "Images/Enemy/TypeOne/Fighter/Base.png"},
	{64, 64, 10, 0.1f, "Images/Enemy/TypeOne/Fighter/Engine.png"},
	{64, 64, 10, 0.09f, "Images/Enemy/TypeOne/Fighter/Shield.png"},
	{64, 64, 8, 0.15f, "Images/Enemy/TypeOne/Fighter/Destruction.png"},
	100, // health
	400 // speed
	})
{
	ListOFActions.emplace_back(std::make_shared<Roam>(this,5.f,(float)window.getSize().x,speed,sf::Vector2f(0,(float)window.getSize().x)));
	ListOFActions.emplace_back(std::make_shared<MoveTo>(this, [&player,this]() { return sf::Vector2f(player.GetPosition().x, GetPosition().y); }));
	AI = std::make_unique<EnemyAI>(ListOFActions);

	sp.SetSize({ 128,128 });
	sp.SetRotation(sf::degrees(180));
	sp.UpdateBaseTexRect(sf::IntRect({ 0, 0 }, { 64,64 }));
	sp.UpdateEngineTexRect(sf::IntRect({ 0, 0 }, { 64,64 }));
	sp.UpdateShieldTexRect(sf::IntRect({ 0, 0 }, { 64,64 }));
}

void Fighter::Draw(sf::RenderWindow& window)
{
	if (IsActive())
		sp.Draw(window);
}

void Fighter::Update(float delta)
{
	
	if(IsActive())
	{
		AI->Update(delta);
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
void Fighter::DestructionEvent(float delta)
{
	if (GetHealth() <= 0 && !IsDestroyed())
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
void Fighter::SetShieldState(bool in_State)
{
	sp.SetShieldState(in_State);
}

void Fighter::SetDestroyedState(bool in_State)
{
	Destroyed = in_State;
}

bool Fighter::IsDestroyed() const
{
	return Destroyed;
}

void Fighter::SetFiringState(bool in_State)
{
	Firing = in_State;
}

bool Fighter::IsFiring() const
{
	return Firing;
}


sf::Vector2f Fighter::GetPosition() const
{
	return sp.GetPosition();
}

sf::Vector2f Fighter::GetSize() const
{
	return sp.GetSize();
}

void Fighter::SetPosition(float x, float y)
{
	sp.SetPosition({ x,y });
}

void Fighter::SetSize(float width, float height)
{
	sp.SetSize({ width,height });
}

bool Fighter::IsActive() const
{
	return ActiveState;
}

void Fighter::SetActive(bool in_state)
{
	ActiveState = in_state;
}

float Fighter::GetTextureOffsetX() const
{
	return XTextureOffset;
}

float Fighter::GetTextureOffsetY() const
{
	return YTextureOffset;
}

float Fighter::GetSpeed() const
{
	return speed;
}

int Fighter::GetHealth() const
{
	return health;
}

void Fighter::SetSpeed(float in_val)
{
	speed = in_val;
}

void Fighter::SetHealth(int in_val)
{
	health = in_val;
}

bool Fighter::IsInWallBoundary() const
{
	float left = GetPosition().x - GetSize().x / 2.f + GetTextureOffsetX();
	float right = GetPosition().x + GetSize().x / 2.f - GetTextureOffsetX();
	float top = GetPosition().y - GetSize().y / 2.f + GetTextureOffsetY();
	float bottom = GetPosition().y + GetSize().y / 2.f - GetTextureOffsetY();

	float winWidth = (float)windowRef.getSize().x;
	float winHeight = (float)windowRef.getSize().y;

	return left >= 0 && right <= winWidth && top >= 0 && bottom <= winHeight;
}

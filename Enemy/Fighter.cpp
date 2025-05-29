#include "Fighter.h"
#include <math.h>

Fighter::Fighter(const sf::Vector2f& pos, sf::RenderWindow& window, Player& player)
	:
	sp(pos,BaseImgPath,EngineImgPath,ShieldImgPath),
	EngineAnim(64, 64, 10, 0.1f),
	ShieldAnim(64, 64, 10, 0.09f),
	FiringAnim(64, 64, 6, 0.03f),
	Enemy(window,player)
{
	ListOFActions.emplace_back(std::make_unique<Roam>(this,5.f,(float)window.getSize().x,speed,sf::Vector2f(0,(float)window.getSize().x)));
	AI = std::make_unique<EnemyAI>(ListOFActions);

	sp.SetSize({ 128,128 });
	sp.SetRotation(sf::degrees(180));
	sp.UpdateBaseTexRect(sf::IntRect({ 0, 0 }, { 64,64 }));
	sp.UpdateEngineTexRect(sf::IntRect({ 0, 0 }, { 64,64 }));
	sp.UpdateShieldTexRect(sf::IntRect({ 0, 0 }, { 64,64 }));
}

void Fighter::Draw(sf::RenderWindow& window)
{
	sp.Draw(window);
}

void Fighter::Update(float delta)
{
	AI->Update(delta);
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
		if (FiringAnim.IsAnimFinished())
		{
			IsFiring = false;
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

#include "Fighter.h"
#include "../../AI/Actions/Roam.h"
#include "../../AI/Actions/MoveTo.h"
#include "../../AI/Actions/FireAction.h"
#include <math.h>
#include <iostream>

Fighter::Fighter(int id, const RandomInfo& randomInfo, sf::RenderWindow& window, Player& player, Pool& bulletPool, Grid& grid)
	:
	Enemy(window,player, randomInfo.initPos,bulletPool,
	{
	{64, 64, 6, 0.1f, "Images/Enemy/TypeOne/Fighter/Base.png"},
	{64, 64, 10, 0.1f, "Images/Enemy/TypeOne/Fighter/Engine.png"},
	{64, 64, 10, 0.09f, "Images/Enemy/TypeOne/Fighter/Shield.png"},
	{64, 64, 8, 0.15f, "Images/Enemy/TypeOne/Fighter/Destruction.png"},
	100, // health
	400 // speed
	}),
	grid(grid),
	InitHealth(GetHealth()),
	id(id)
{

	//Socket Positions
	BulletsSocket.push_back({ -15.f,15.f }); // left socket
	BulletsSocket.push_back({ 15.f,15.f }); // right socket
	FrameOfFire.push_back(2);// fires at frame 2
	FrameOfFire.push_back(4);// same at 4
	InitPos = randomInfo.initPos;
	ListOFActions.emplace_back(std::make_shared<MoveTo>(this, [&player, randomInfo, this]() { return randomInfo.destinationPos; }));
	ListOFActions.emplace_back(std::make_shared<Roam>(this, randomInfo.RoamDuration,0,(float)window.getSize().x,speed));
	ListOFActions.emplace_back(std::make_shared<MoveTo>(this, [&player,this]() { return sf::Vector2f(player.GetPosition().x, GetPosition().y); }));
	ListOFActions.emplace_back(std::make_shared<FireAction>(this));
	ListOFActions.emplace_back(std::make_shared<MoveTo>(this, [&player,this]() { return sf::Vector2f(player.GetPosition().x, GetPosition().y); }));
	ListOFActions.emplace_back(std::make_shared<FireAction>(this));

	AI = std::make_unique<EnemyAI>(ListOFActions);

	sp.SetSize({ 128,128 });
	sp.SetRotation(sf::degrees(180));
	sp.UpdateBaseTexRect(sf::IntRect({ 0, 0 }, { 64,64 }));
	sp.UpdateEngineTexRect(sf::IntRect({ 0, 0 }, { 64,64 }));
	sp.UpdateShieldTexRect(sf::IntRect({ 0, 0 }, { 64,64 }));

	Info.id = id;
	Info.Position = GetPosition();
	Info.Size = GetSize() / 4.f;
	Info.EntityType = GetType();
	

	grid.AddToGrid(Info);
}

void Fighter::Draw(sf::RenderWindow& window)
{
	if (IsActive())
	{
		sp.Draw(window);
	}

}
void Fighter::Update(float delta)
{
	
	if(IsActive())
	{
		DestructionEvent(delta);
		if(IsActive() && !IsDestroyed())
		{
			OnHit();
			AI->Update(delta);
			AIBehaviour();
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
void Fighter::Respawn()
{
	SetDestroyedState(false);
	SetHealth(InitHealth);
	SetPosition(InitPos.x, InitPos.y);
	sp.DeactiveDestruction();
	sp.SetEngineState(true);
	{
		AI->Reset();
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
		grid.RemoveFromGrid(Info);
		DestructionAnim.Update(delta);
		sp.UpdateBaseTexRect(DestructionAnim.GetCurrentFrame());
		if (DestructionAnim.IsAnimFinished())
		{
			SetActive(false);
			Respawn();
		}
	}
}


void Fighter::RetrieveBullet()
{
	if(!BulletList.empty())
	{
		BulletList.clear();
	}
	for (int i = 0; i < BulletsSocket.size(); i++)
	{
		BulletList.push_back(dynamic_cast<Bullets*>(BulletPool.GetFreeEntity()));
	}
}

void Fighter::AIBehaviour()
{
	if(player.GetPosition().y < GetPosition().y && ShootingDir)
	{
		ShootingDir = false;
		sp.SetRotation(sf::degrees(0));
	}
	if (player.GetPosition().y > GetPosition().y && !ShootingDir)
	{
		ShootingDir = true;
		sp.SetRotation(sf::degrees(180));
	}
	if(IsMoving())
	{
		Info.Position = GetPosition();
		grid.AddToGrid(Info);
	}
}
void Fighter::OnHit()
{
	if (grid.IsEntityCollides(Info))
	{
		Info.Position = GetPosition();
		auto Entities = grid.GetCollidedEntites(Info);
		for (const auto& e : Entities)
		{
			//its not a bullet && its not damaging the shooter(player bullet doesn't damage the player)
			if (e.EntityType == Type::playerBullet)
			{
				SetHealth(GetHealth() - 10);
			}
		}
	}
}
Boundary Fighter::WallBoundary() const
{
	Boundary b;
	b.left = 0;
	b.right = (float)windowRef.getSize().x;
	b.top = 0;
	b.bottom = (float)windowRef.getSize().y;
	return b;
}
Boundary Fighter::entityBoundary() const
{	
	Boundary b;
	b.left = GetPosition().x - GetSize().x / 2.f + GetTextureOffsetX();
	b.right = GetPosition().x + GetSize().x / 2.f - GetTextureOffsetX();
	b.top = GetPosition().y + GetSize().y / 2.f - GetTextureOffsetY();
	b.bottom = GetPosition().y + GetSize().y / 2.f - GetTextureOffsetY();
	return b;
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
bool Fighter::IsActive() const
{
	return ActiveState;
}

void Fighter::SetActive(bool in_state)
{
	ActiveState = in_state;
}

void Fighter::SetMoving(bool in_State)
{
	Moving = in_State;
}

bool Fighter::IsMoving() const
{
	return Moving;
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



int Fighter::GetFireCurrentFrame() const
{
	return FiringAnim.GetCurrentIndex();
}



std::vector<sf::Vector2f> Fighter::GetSockets() const
{
	return BulletsSocket;
}

std::vector<int> Fighter::GetFrameOfFire() const
{
	return FrameOfFire;
}

std::vector<Bullets*>& Fighter::GetBullets()
{
	return BulletList;
}

Type Fighter::GetType() const
{
	return type;
}

bool Fighter::GetShootDir() const
{
	return ShootingDir;
}
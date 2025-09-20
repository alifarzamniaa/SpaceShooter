#include "EliteFighter.h"
#include "../../AI/Actions/WaveRoam.h"
#include "../../AI/Actions/MoveTo.h"
#include "../../AI/Actions/FireAction.h"
#include <math.h>
#include <iostream>

EliteFighter::EliteFighter(int id, const RandomInfo& randomInfo, sf::RenderWindow& window, Player& player, Pool& bulletPool, Grid& grid)
	:
	Enemy(window, player, randomInfo.initPos, bulletPool,
		{
		{64, 64, 16, 0.1f, "Images/Enemy/TypeOne/EliteFighter/Base.png"},
		{64, 64, 10, 0.1f, "Images/Enemy/TypeOne/EliteFighter/Engine.png"},
		{64, 64, 10, 0.09f, "Images/Enemy/TypeOne/EliteFighter/Shield.png"},
		{64, 64, 10, 0.15f, "Images/Enemy/TypeOne/EliteFighter/Destruction.png"},
		200, // health
		300 // speed
		}),
	grid(grid),
	InitHealth(GetHealth()),
	id(id)
{

	//Socket Positions
	BulletsSocket.push_back({ -15.f,15.f });

	BulletsSocket.push_back({ 15.f,15.f });

	BulletsSocket.push_back({ -30.f,15.f });

	BulletsSocket.push_back({ 30.f,15.f });

	BulletsSocket.push_back({ -40.f,15.f });

	BulletsSocket.push_back({ 40.f,15.f });

	//Missle released frame number
	FrameOfFire.push_back(5);
	FrameOfFire.push_back(7);
	FrameOfFire.push_back(9);
	FrameOfFire.push_back(11);
	FrameOfFire.push_back(13);
	FrameOfFire.push_back(15);

	InitPos = randomInfo.initPos;
	WaveRoamProp waveProp;
	waveProp.TaskDuration = randomInfo.RoamDuration;
	waveProp.MinRangeX = 0;
	waveProp.MinRangeX = (float)window.getSize().x;
	waveProp.MinRangeY = 0;
	waveProp.MaxRangeY = (float)window.getSize().y / 2.f;
	waveProp.amplitude = 0.2f;
	waveProp.frequency = 5.f;
	waveProp.dir = WaveDirection::XWave;
	waveProp.speed = speed;

	ListOFActions.emplace_back(std::make_shared<MoveTo>(this, [randomInfo, this]() { return randomInfo.destinationPos; }));
	ListOFActions.emplace_back(std::make_shared<WaveRoam>(this,waveProp));
	ListOFActions.emplace_back(std::make_shared<MoveTo>(this, [&player, this]() { return sf::Vector2f(player.GetPosition().x, GetPosition().y); }));
	ListOFActions.emplace_back(std::make_shared<FireAction>(this));
	ListOFActions.emplace_back(std::make_shared<MoveTo>(this, [&player, this]() { return sf::Vector2f(player.GetPosition().x, GetPosition().y); }));
	ListOFActions.emplace_back(std::make_shared<FireAction>(this));

	AI = std::make_unique<EnemyAI>(ListOFActions);

	sp.SetSize({ 128,128 });
	sp.SetRotation(sf::degrees(180));
	sp.UpdateBaseTexRect(sf::IntRect({ 0, 0 }, { 64,64 }));
	sp.UpdateEngineTexRect(sf::IntRect({ 0, 0 }, { 64,64 }));
	sp.UpdateShieldTexRect(sf::IntRect({ 0, 0 }, { 64,64 }));

	Info.id = id;
	Info.Position = GetPosition();
	Info.Size = {GetSize().x / 2.f ,GetSize().y / 4.f };
	Info.EntityType = GetType();

	grid.AddToGrid(Info);
}

void EliteFighter::Draw(sf::RenderWindow& window)
{
	if (IsActive())
	{
		sp.Draw(window);
	}

}
void EliteFighter::Update(float delta)
{

	if (IsActive())
	{
		DestructionEvent(delta);
		if (IsActive() && !IsDestroyed())
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
void EliteFighter::Respawn()
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
void EliteFighter::DestructionEvent(float delta)
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
		}
	}
}


void EliteFighter::RetrieveBullet()
{
	if (!BulletList.empty())
	{
		BulletList.clear();
	}
	for (int i = 0; i < BulletsSocket.size(); i++)
	{
		BulletList.push_back(dynamic_cast<Bullets*>(BulletPool.GetFreeEntity()));
	}
}

void EliteFighter::AIBehaviour()
{
	if (player.GetPosition().y < GetPosition().y && ShootingDir)
	{
		ShootingDir = false;
		sp.SetRotation(sf::degrees(0));
	}
	if (player.GetPosition().y > GetPosition().y && !ShootingDir)
	{
		ShootingDir = true;
		sp.SetRotation(sf::degrees(180));
	}
	if (IsMoving())
	{
		Info.Position = GetPosition();
		grid.AddToGrid(Info);
	}
}
void EliteFighter::OnHit()
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
Boundary EliteFighter::WallBoundary() const
{
	Boundary b;
	b.left = 0;
	b.right = (float)windowRef.getSize().x;
	b.top = 0;
	b.bottom = (float)windowRef.getSize().y;
	return b;
}
Boundary EliteFighter::entityBoundary() const
{
	Boundary b;
	b.left = GetPosition().x - GetSize().x / 2.f + GetTextureOffsetX();
	b.right = GetPosition().x + GetSize().x / 2.f - GetTextureOffsetX();
	b.top = GetPosition().y - GetSize().y / 2.f + GetTextureOffsetY();
	b.bottom = GetPosition().y + GetSize().y / 2.f - GetTextureOffsetY();
	return b;
}
void EliteFighter::SetShieldState(bool in_State)
{
	sp.SetShieldState(in_State);
}

void EliteFighter::SetDestroyedState(bool in_State)
{
	Destroyed = in_State;
}

bool EliteFighter::IsDestroyed() const
{
	return Destroyed;
}

void EliteFighter::SetFiringState(bool in_State)
{
	Firing = in_State;
}

bool EliteFighter::IsFiring() const
{
	return Firing;
}
bool EliteFighter::IsActive() const
{
	return ActiveState;
}

void EliteFighter::SetActive(bool in_state)
{
	if (!ActiveState && in_state == true)
	{
		Respawn();
	}
	ActiveState = in_state;
}

void EliteFighter::SetMoving(bool in_State)
{
	Moving = in_State;
}

bool EliteFighter::IsMoving() const
{
	return Moving;
}

float EliteFighter::GetTextureOffsetX() const
{
	return XTextureOffset;
}

float EliteFighter::GetTextureOffsetY() const
{
	return YTextureOffset;
}

float EliteFighter::GetSpeed() const
{
	return speed;
}

int EliteFighter::GetHealth() const
{
	return health;
}

void EliteFighter::SetSpeed(float in_val)
{
	speed = in_val;
}

void EliteFighter::SetHealth(int in_val)
{
	health = in_val;
}
sf::Vector2f EliteFighter::GetPosition() const
{
	return sp.GetPosition();
}

sf::Vector2f EliteFighter::GetSize() const
{
	return sp.GetSize();
}

void EliteFighter::SetPosition(float x, float y)
{
	sp.SetPosition({ x,y });
}

void EliteFighter::SetSize(float width, float height)
{
	sp.SetSize({ width,height });
}


int EliteFighter::GetFireCurrentFrame() const
{
	return FiringAnim.GetCurrentIndex();
}



std::vector<sf::Vector2f> EliteFighter::GetSockets() const
{
	return BulletsSocket;
}

std::vector<int> EliteFighter::GetFrameOfFire() const
{
	return FrameOfFire;
}

std::vector<Bullets*>& EliteFighter::GetBullets()
{
	return BulletList;
}

Type EliteFighter::GetType() const
{
	return type;
}

bool EliteFighter::GetShootDir() const
{
	return ShootingDir;
}
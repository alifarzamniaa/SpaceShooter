#include "Fighter.h"
#include "../../AI/Actions/Roam.h"
#include "../../AI/Actions/MoveTo.h"
#include "../../AI/Actions/FireAction.h"
#include <math.h>

Fighter::Fighter(const sf::Vector2f& pos, sf::RenderWindow& window, Player& player, Pool& bulletPool)
	:
	Enemy(window,player,pos,bulletPool,
	{
	{64, 64, 6, 0.1f, "Images/Enemy/TypeOne/Fighter/Base.png"},
	{64, 64, 10, 0.1f, "Images/Enemy/TypeOne/Fighter/Engine.png"},
	{64, 64, 10, 0.09f, "Images/Enemy/TypeOne/Fighter/Shield.png"},
	{64, 64, 8, 0.15f, "Images/Enemy/TypeOne/Fighter/Destruction.png"},
	{8, 16, 4, 0.1f, "Images/Bullets/Enemy/Type1/FighterBullet.png"},
	"Images/Bullets/Enemy/Type1/FighterBullet.png",
	100, // health
	400 // speed
	})
{
	ListOFActions.emplace_back(std::make_shared<Roam>(this,3.f,(float)window.getSize().x,speed,sf::Vector2f(0,(float)window.getSize().x)));
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


	//Socket Positions
	BulletsSocket.push_back({-10.f,15.f}); // left socket
	BulletsSocket.push_back({10.f,15.f}); // right socket
	FrameOfFire.push_back(2);// fires at frame 2
	FrameOfFire.push_back(4);// same at 4
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

sf::Texture& Fighter::GetBulletTex()
{
	return BulletTex;
}
Animation Fighter::GetBulletAnim() const
{
	return BulletAnim;
}

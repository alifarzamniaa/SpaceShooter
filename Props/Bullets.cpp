#include "Bullets.h"
#include <iostream>

Bullets::Bullets(float width, float height, const sf::Texture& bulletModel, const Animation& bulletAnim, const sf::IntRect& TexRect, float fireSpeed, int windowHeight)
	:
	bulletAnim(bulletAnim),
	speed(fireSpeed),
	windowHeight(windowHeight)
{
	bullet.setSize({width,height});
	bullet.setTexture(&bulletModel);
	bullet.setTextureRect(TexRect);
	bullet.setOrigin(bullet.getSize() / 2.f);
}

void Bullets::Update(float delta)
{
	bulletAnim.Update(delta);
	bullet.setTextureRect(bulletAnim.GetCurrentFrame());
	Fire(delta);
	//disabled when out of screen
	if(GetPosition().y < 0 || GetPosition().y >= windowHeight)
		SetActive(false);
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

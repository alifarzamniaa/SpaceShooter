#include "Bullets.h"
#include <iostream>

Bullets::Bullets(float width, float height, const sf::Texture& bulletModel, const Animation& bulletAnim, const sf::IntRect& TexRect, float fireSpeed, int windowHeight, bool Dir)
	:
	bulletAnim(bulletAnim),
	speed(fireSpeed),
	Direction(Dir),
	windowHeight(windowHeight)
{
	bullet.setSize({width,height});
	bullet.setTexture(&bulletModel);
	bullet.setTextureRect(TexRect);
	bullet.setOrigin(bullet.getSize() / 2.f);
	if(Direction)
		bullet.setRotation(sf::degrees(180.f));
}

void Bullets::Update(float delta)
{
	bulletAnim.Update(delta);
	bullet.setTextureRect(bulletAnim.GetCurrentFrame());
	//negative shoots upward , positive shoot downward
	float vel = Direction ? speed * delta : -speed * delta;
	bullet.move(sf::Vector2f{ 0,vel });
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

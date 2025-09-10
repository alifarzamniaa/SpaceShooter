#include "SpaceShip.h"
#include <iostream>
SpaceShip::SpaceShip(const sf::Vector2f& pos, const std::string& baseModel, const std::string& engineModel, const std::string& shieldModel, const std::string& DestructionModel)
{
	if(!baseT.loadFromFile(baseModel))
	{
		std::cout <<"!!!Loading Error : Could NOT load image for base model!\n";
	}
	if (!engineT.loadFromFile(engineModel))
	{
		std::cout << "!!!Loading Error : Could NOT load image for shield model!\n";
	}
	if (!shieldT.loadFromFile(shieldModel))
	{
		std::cout << "!!!Loading Error : Could NOT load image for engine model!\n";
	}
	if (!DestructionT.loadFromFile(DestructionModel))
	{
		std::cout << "destruction texture is NOT Loaded!!\n";
	}
	base.setTexture(&baseT);
	engine.setTexture(&engineT);
	shield.setTexture(&shieldT);

	base.setSize((sf::Vector2f)baseT.getSize());
	engine.setSize(base.getSize());
	shield.setSize(base.getSize());

	base.setOrigin(base.getSize() / 2.f);
	engine.setOrigin(engine.getSize() / 2.f);
	shield.setOrigin(shield.getSize() / 2.f);

	base.setPosition(pos);
	engine.setPosition(pos);
	shield.setPosition(pos);
}

void SpaceShip::ChangeBaseModelTex(const sf::Texture& tex)
{
	base.setTexture(&tex);
}

void SpaceShip::ChangeEngineModelTex(const sf::Texture& tex)
{
	engine.setTexture(&tex);
}
void SpaceShip::ChangeShieldModelTex(const sf::Texture& tex)
{
	shield.setTexture(&tex);
}

void SpaceShip::UpdateBaseTexRect(const sf::IntRect& in_rect)
{
	base.setTextureRect(in_rect);
}

void SpaceShip::UpdateEngineTexRect(const sf::IntRect& in_rect)
{
	engine.setTextureRect(in_rect);
}

void SpaceShip::UpdateShieldTexRect(const sf::IntRect& in_rect)
{
	shield.setTextureRect(in_rect);
}
void SpaceShip::SetSize(const sf::Vector2f& in_size)
{
	base.setSize(in_size);
	engine.setSize(in_size);
	shield.setSize(in_size);

	// when resizing the origin will change, origin in my design is on center
	base.setOrigin(base.getSize() / 2.f);
	engine.setOrigin(engine.getSize() / 2.f);
	shield.setOrigin(shield.getSize() / 2.f);
}

void SpaceShip::SetShieldState(bool in_state)
{
	IsShieldActive = in_state;
}

void SpaceShip::SetEngineState(bool in_state)
{
	IsEngineActive = in_state;
}

void SpaceShip::ActiveDestruction()
{
	ChangeBaseModelTex(DestructionT);
}

void SpaceShip::DeactiveDestruction()
{
	ChangeBaseModelTex(baseT);
}

void SpaceShip::SetRotation(const sf::Angle& in_rot)
{
	base.setRotation(in_rot);
	engine.setRotation(in_rot);
	shield.setRotation(in_rot);
}

void SpaceShip::SetPosition(const sf::Vector2f& in_pos)
{
	base.setPosition(in_pos);
	engine.setPosition(in_pos);
	shield.setPosition(in_pos);
}

void SpaceShip::Draw(sf::RenderWindow& window)
{
	window.draw(base);
	if(IsEngineActive)
		window.draw(engine);
	if(IsShieldActive)
		window.draw(shield);
}

sf::Angle SpaceShip::GetRotation() const
{
	return base.getRotation();
}

sf::Vector2f SpaceShip::GetPosition() const
{
	return base.getPosition();
}

sf::Vector2f SpaceShip::GetSize() const
{
	return base.getSize();
}

bool SpaceShip::GetShieldState() const
{
	return IsShieldActive;
}

bool SpaceShip::GetEngineState() const
{
	return IsEngineActive;
}

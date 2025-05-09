#include "SpaceShip.h"
#include <iostream>
SpaceShip::SpaceShip(const sf::Vector2f& pos, const std::string& baseModel, const std::string& engineModel, const std::string& shieldModel)
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
	
	base.setTexture(&baseT);
	engine.setTexture(&engineT);
	shield.setTexture(&shieldT);

	base.setSize((sf::Vector2f)baseT.getSize());
	engine.setSize(base.getSize());
	shield.setSize(base.getSize());

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
}

void SpaceShip::SetShieldState(bool in_state)
{
	IsShieldActive = in_state;
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
	window.draw(engine);
	if(IsShieldActive)
		window.draw(shield);
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

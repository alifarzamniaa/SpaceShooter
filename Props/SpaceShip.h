#pragma once
#include <SFML/Graphics.hpp>
class SpaceShip
{
public:
	//constructor
	SpaceShip(const sf::Vector2f& pos,const std::string& baseModel, const std::string& engineModel,const std::string& shieldModel,const std::string& DestructionModel);

	//changing texture for each part
	void ChangeBaseModelTex(const sf::Texture& tex);
	void ChangeEngineModelTex(const sf::Texture& tex);
	void ChangeShieldModelTex(const sf::Texture& tex);

	//changing the area to display from texture
	void UpdateBaseTexRect(const sf::IntRect& in_rect);
	void UpdateEngineTexRect(const sf::IntRect& in_rect);
	void UpdateShieldTexRect(const sf::IntRect& in_rect);

	//chaning state of the spaceship
	void SetShieldState(bool in_state);
	void SetEngineState(bool in_state);
	void ActiveDestruction();
	void SetRotation(const sf::Angle& in_rot);
	void SetPosition(const sf::Vector2f& in_pos);
	void SetSize(const sf::Vector2f& in_size);
	
	//getting the states
	sf::Angle GetRotation() const;
	sf::Vector2f GetPosition() const;
	sf::Vector2f GetSize() const;
	bool GetShieldState() const;
	bool GetEngineState() const;
	
	void Draw(sf::RenderWindow& window);
	
private:
	sf::RectangleShape base;
	sf::RectangleShape engine;
	sf::RectangleShape shield;

	sf::Texture baseT;
	sf::Texture engineT;
	sf::Texture shieldT;
	sf::Texture DestructionT;

	bool IsShieldActive = false;
	bool IsEngineActive = true;
	bool IsDestructionActive = true;
};
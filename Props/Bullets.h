#pragma once
#include <SFML/Graphics.hpp>
#include "../Animation.h"
#include "../Entity.h"
class Bullets : public Entity
{
public:
	// direction : false make it move upwards , true make it downwards;
	Bullets(float width, float height, const sf::Texture& bulletModel,const Animation& bulletAnim,const sf::IntRect& TexRect,float fireSpeed, bool Dir = false);
	
	void Update(float delta) override; 
	void Draw(sf::RenderWindow& window) override;

	sf::Vector2f GetPosition() const override;
	sf::Vector2f GetSize() const override;

	void SetPosition(float x, float y) override;
	void SetSize(float width, float height) override;

	void SetDestroyedState(bool in_State) override;
	bool IsDestroyed() const override;

	bool IsActive() const override;
	void SetActive(bool in_state) override;
private:
	sf::RectangleShape bullet;
	Animation bulletAnim;
	float speed = 100.f;
	bool ActiveState = false;
	// direction : false make it move upwards , true make it downwards;
	bool Direction = false;
	bool Destroyed = false;
};


#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
class Bullets
{
public:
	Bullets(float width, float height, const sf::Texture& bulletModel,const Animation& bulletAnim,const sf::IntRect& TexRect,float fireSpeed);
	// direction : false make it move upwards , true make it downwards;
	void Fire(float delta,bool direction = false); 
	void Draw(sf::RenderWindow& window, float delta);
	void SetSize(float width, float height);
	void SetPosition(float x, float y);
	void SetActive(bool in_state);

	sf::Vector2f GetPosition() const;
	sf::Vector2f GetSize() const;
	bool IsActive() const;
private:
	sf::RectangleShape bullet;
	Animation bulletAnim;
	float speed = 100.f;
	bool ActiveState = false;

};


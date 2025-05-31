#pragma once
#include <SFML/Graphics.hpp>
class Entity
{
public:
	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual void Update(float delta) = 0;

	virtual sf::Vector2f GetPosition() const = 0;
	virtual sf::Vector2f GetSize() const = 0;

	virtual void SetPosition(float x, float y) = 0;
	virtual void SetSize(float width, float height) = 0;

	virtual bool IsActive() const = 0;
	virtual void SetActive(bool in_state) = 0;

	virtual void SetDestroyedState(bool in_State) = 0;
	virtual bool IsDestroyed() const = 0;

};
#pragma once
#include "SFML/Audio.hpp"
#include "../../Entity.h"
#include "../Grid.h"
class HealthItem : public Entity
{
public:
	HealthItem(const sf::Texture& tex,Grid& grid,int Id);
	void Draw(sf::RenderWindow& window) override;
	void Update(float delta) override;

	sf::Vector2f GetPosition() const override;
	sf::Vector2f GetSize() const override;

	void SetPosition(float x, float y) override;
	void SetSize(float width, float height) override;

	bool IsActive() const override;
	void SetActive(bool in_state) override;
	void OnHit() override;
	void SetDestroyedState(bool in_State) override;
	bool IsDestroyed() const override;
	Type GetType() const override;
	float GetHPRestoration() const;
private:
	sf::RectangleShape healthBox;
	Grid& grid;
	//determines how fast health goes down
	float speed; 
	Type type = Type::IHealth;
	CellEntityInfo Info;
	sf::SoundBuffer OnHitSoundBuffer;
	sf::Sound OnHitSound;
	bool ActiveState;
	bool Destroyed;
};
#pragma once
#include "Enemy.h"
#include "../AI/EnemyAI.h"
#include "../Props/SpaceShip.h"
#include "../Animation.h"
class Fighter : public Enemy
{
public:
	Fighter(const sf::Vector2f& pos,sf::RenderWindow& window, Player& player);
	void Draw(sf::RenderWindow& window) override;
	void Update(float delta) override;

	void SetShieldState(bool in_State) override;
	void SetDestroyedState(bool in_State) override;
	bool IsDestroyed() const override;
	void SetFiringState(bool in_State) override;
	bool IsFiring() const override;

	sf::Vector2f GetPosition() const override;
	sf::Vector2f GetSize() const override;

	void SetPosition(float x, float y) override;
	void SetSize(float width, float height) override;

	bool IsActive() const override;
	void SetActive(bool in_state) override;


	// Returns the horizontal offset needed for accurate collision detection,
	// in case the texture size doesn't match the visual rectangle size.
	// returns 0 if texture is the same size as the rectangle
	float GetTextureOffsetX() const override;
	// Returns the vertical offset needed for accurate collision detection,
	// in case the texture size doesn't match the visual rectangle size.
	// returns 0 if texture is the same size as the rectangle
	float GetTextureOffsetY() const override;

	float GetSpeed() const override;
	int GetHealth() const override;
	void SetSpeed(float in_val) override;
	void SetHealth(int in_val) override;
	bool IsInWallBoundary() const override;
private:
	// logic for destruction and when health is <= 0 
	void DestructionEvent(float delta) override;
private:
	// texture may not be the same size as rect itself and may cause to inaccurate collision
	// this value is for vertical offset used to adjust collision detection
	// change this to get more accurate collision or make it 0 for texture that is the same size as rectangle
	float XTextureOffset = 30.f;
	// texture may not be the same size as rect itself and may cause to inaccurate collision
	// this value is for vertical offset used to adjust collision detection
	// change this to get more accurate collision or make it 0 for texture that is the same size as rectangle
	float YTextureOffset = 20.f;

	//objects
	std::unique_ptr<EnemyAI> AI;
	std::vector<std::shared_ptr<AIAction>> ListOFActions;

	bool Firing = false;
	bool ActiveState = true;
	bool Destroyed = false;
	float Dir;
	float InitPosX;
};


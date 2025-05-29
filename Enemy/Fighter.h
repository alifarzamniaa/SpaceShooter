#pragma once
#include "Enemy.h"
#include "../AI/EnemyAI.h"
#include "../AI/Actions/Roam.h"
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

	sf::Vector2f GetPosition() const override;
	sf::Vector2f GetSize() const override;

	void SetPosition(float x, float y) override;
	void SetSize(float width, float height) override;

	bool IsActive() const override;
	void SetActive(bool in_state) override;

	// texture may not be the same size as rect itself and may cause to inaccurate collision
	// this returns horizontal offset used to adjust collision detection
	// returns 0 if texture is the same size as the rectangle
	float GetTextureOffsetX() const override;
	// texture may not be the same size as rect itself and may cause to inaccurate collision
	// this returns vertical offset used to adjust collision detection
	// returns 0 if texture is the same size as the rectangle
	float GetTextureOffsetY() const override;
private:
	//Custom Properties
	std::string BaseImgPath = "Images/Enemy/TypeOne/Fighter/Base.png";
	std::string EngineImgPath = "Images/Enemy/TypeOne/Fighter/Engine.png";
	std::string ShieldImgPath = "Images/Enemy/TypeOne/Fighter/Shield.png";
	float speed = 400.f;
	float health;

	// texture may not be the same size as rect itself and may cause to inaccurate collision
	// this value is for vertical offset used to adjust collision detection
	// change this to get more accurate collision or make it 0 for texture that is the same size as rectangle
	float XTextureOffset = 30.f;
	// texture may not be the same size as rect itself and may cause to inaccurate collision
	// this value is for vertical offset used to adjust collision detection
	// change this to get more accurate collision or make it 0 for texture that is the same size as rectangle
	float YTextureOffset = 20.f;

	//objects
	SpaceShip sp;
	std::unique_ptr<EnemyAI> AI;
	Animation FiringAnim;
	Animation EngineAnim;
	Animation ShieldAnim;
	std::vector<std::shared_ptr<AIAction>> ListOFActions;

	bool IsFiring = false;
	bool ActiveState = true;
	bool Destroyed = false;
	float Dir;
	float InitPosX;
};


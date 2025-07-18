#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Props/SpaceShip.h"
#include "Animation.h"
#include "Props/Bullets.h"
#include "Props/Pool.h"
#include "Props/Grid.h"
class Player : public Entity
{
public:
	Player(const sf::Vector2f& pos);	
	void Draw(sf::RenderWindow& window) override;
	void Update(float delta) override;

	sf::Vector2f GetPosition() const override;
	sf::Vector2f GetSize() const override;

	void SetPosition(float x, float y) override;
	void SetSize(float width, float height) override;

	bool IsActive() const override;
	void SetActive(bool in_state) override;

	void SetDestroyedState(bool in_State) override;
	bool IsDestroyed() const override;
	void OnHit(Grid& grid);
	void SetFiringState(bool in_State) ;
	bool IsFiring() const;

	float GetSpeed() const;
	int GetHealth() const;

	void SetSpeed(float in_val);
	void SetHealth(int in_val);

	void Movement(float delta, const sf::Vector2f& leftRightBound, const sf::Vector2f& TopBottomBound);
	void WallCollision(const sf::Vector2f& leftRightBound, const sf::Vector2f& topBottomBound);
	void DestructionEvent(float delta);
	void Actions(float delta, Pool& bulletPool, std::optional<sf::Event> e);
	
	sf::Texture& GetBulletTex();
	Animation GetBulletAnim();

	std::vector<sf::Vector2i>& GetLastOccupied() override;
	void SetOccupied(std::vector<sf::Vector2i>& occupiedSpace) override;
	std::string GetTag() const override;
private:
	//Custom Properties
	std::string BaseImgPath = "Images/Player/Weapon.png";
	std::string EngineImgPath = "Images/Player/Engine.png";
	std::string ShieldImgPath = "Images/Player/Shield.png";
	std::string DestructionImgPath = "Images/Player/Destruction.png";
	std::string BulletImgPath = "Images/Bullets/PlayerBullet.png";

	std::string Tag = "Player";
	//this is used for if texture is smaller than the box, you can adjust the gap between box and texture to make collision more accurate
	float verticalPadding = 20.f;
	// same as vertical but for horizontal part
	float horizontalPadding = 15.f;

	int health = 100;
	float playerShipSize = 100.f;
	float speed = 500.f;
	float ShieldCooldown = 20.f; // in seconds
	float ShieldDuration = 5.f; // in seconds
	//change its value on constructor
	sf::Vector2f LBulletSocket = sf::Vector2f(-10.f, -15.f); // left Socket
	sf::Vector2f RBulletSocket = sf::Vector2f(10.f, -15.f); // Right Socket

	//==========================================================================
	//obj
	SpaceShip sp;
	sf::Texture BulletTex;
	Animation FiringAnim;
	Animation EngineAnim;
	Animation ShieldAnim;
	Animation BulletAnim;
	Animation DestructionAnim;
	std::vector<sf::Vector2i> LastOccupied;

	bool ActiveState = true;
	bool Firing = false;
	bool Destroyed = false;
};


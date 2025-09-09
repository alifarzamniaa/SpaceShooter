#pragma once
#include <SFML/Graphics.hpp>
#include "../Animation.h"
#include "../Entity.h"
#include "Grid.h"
#include "SFML/Audio.hpp"
#include "Particle.h"
class Bullets : public Entity
{
public:
	// direction : false make it move upwards , true make it downwards;
	Bullets(int id,float width, float height, const sf::Texture& bulletModel,const Animation& bulletAnim,const sf::IntRect& TexRect,float fireSpeed, int windowHeight,const Type& Bullettype,const Type& ShooterType,Grid& grid);
	
	void Update(float delta) override; 
	void Draw(sf::RenderWindow& window) override;
	void Fire(float delta);
	sf::Vector2f GetPosition() const override;
	sf::Vector2f GetSize() const override;

	void SetPosition(float x, float y) override;
	void SetSize(float width, float height) override;

	void SetDestroyedState(bool in_State) override;
	bool IsDestroyed() const override;

	void OnHit() override;
	bool IsActive() const override;
	void SetActive(bool in_state) override;
	bool GetDirection() const;
	void SetDirection(bool in_val);
	Type GetType() const override;
	void DestructionEvent(float delta);
private:
	sf::RectangleShape bullet;
	Animation bulletAnim;
	std::vector<sf::Vector2i> LastOccupied;
	float speed = 100.f;
	bool ActiveState = false;
	// direction : false make it move upwards , true make it downwards;
	bool Direction = false;
	bool Destroyed = false;
	int windowHeight;
	Type type;
	Type ShootersType;
	CellEntityInfo Info;
	Grid& grid;
	sf::SoundBuffer FireSoundBuffer;
	sf::Sound FireSound;
	Particle onHitParticle;
};


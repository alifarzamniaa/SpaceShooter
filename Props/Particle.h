#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "../../Animation.h"
struct ParticleProperties
{
	float width;
	float height;
	int FrameWidth;
	int FrameHeight;
	int frameNumbers;
	float duration;
};
class Particle
{
public:
	Particle(const std::string& particlePath, const std::string& particleSoundPath,const ParticleProperties& AnimProperties);
	void ActivateParticle();
	void Play(const sf::Vector2f& SpawnAtLocation, float delta);
	void Draw(sf::RenderWindow& window);
	bool IsFinished() const;
private:
	sf::RectangleShape particle;
	sf::Texture particleTex;
	std::unique_ptr<sf::Sound> particleSoundPtr;
	sf::SoundBuffer soundBuffer;
	Animation ParticleAnim;
	bool IsActive;
};
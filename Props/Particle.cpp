#include "Particle.h"
#include <iostream>
Particle::Particle(const std::string& particlePath, const std::string& particleSoundPath, const ParticleProperties& AnimProperties)
	:
	ParticleAnim(AnimProperties.FrameWidth, AnimProperties.FrameHeight, AnimProperties.frameNumbers, AnimProperties.duration)
{
	IsActive = false;
	particle.setSize({AnimProperties.width,AnimProperties.height });
	particle.setOrigin(particle.getSize() / 2.f);
	if(particleTex.loadFromFile(particlePath))
	{
		particle.setTexture(&particleTex);
	}else
	{
		std::cout << "Could not load particle effect Texture Maybe FilePath is wrong!!!\n";
	}
	if(soundBuffer.loadFromFile(particleSoundPath))
	{
		particleSoundPtr = std::make_unique<sf::Sound>(soundBuffer);
	}
	else
	{
		std::cout << "Could not load particle effect Sound Maybe FilePath is wrong!!!\n";
	}
}

void Particle::ActivateParticle()
{
	IsActive = true;
	if (particleSoundPtr)
	{
		particleSoundPtr->play();
	}
}
void Particle::Draw(sf::RenderWindow& window)
{
	if(IsActive)
	{
		window.draw(particle);
	}
}
bool Particle::IsFinished() const
{
	return !IsActive;
}
void Particle::Play(const sf::Vector2f& SpawnAtLocation,float delta)
{ 
	if(IsActive)
	{
		particle.setPosition(SpawnAtLocation);	
		ParticleAnim.Update(delta);
		particle.setTextureRect(ParticleAnim.GetCurrentFrame());
		if(ParticleAnim.IsAnimFinished())
		{
			IsActive = false;
		}
	}
}


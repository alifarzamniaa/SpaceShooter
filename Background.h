#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class Background
{
public:
	Background(const sf::RenderWindow& window,float speed);
	void Update(float delta, const sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
private:
	std::vector<sf::RectangleShape> bgs;
	std::vector<sf::Texture> bgsTexture;
	float speed;
};


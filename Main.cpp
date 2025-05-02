#include <SFML/Graphics.hpp>
#include "Player.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode({700,900}),"Space Shooter");
	sf::Clock clock;
	Player player({100.f,100.f});
	while(window.isOpen())
	{
		while(const auto Event = window.pollEvent())
		{
			if(Event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}
		float delta = clock.restart().asSeconds();
		window.clear();
		player.Movement(delta,{0,(float)window.getSize().x},{0,(float)window.getSize().y});
		player.Draw(window,delta);
		window.display();
	}
	return 0;
}
#include <SFML/Graphics.hpp>
#include "Player.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode({700,900}),"Space Shooter");
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
		
		window.clear();
		player.Draw(window);
		window.display();
	}
	return 0;
}
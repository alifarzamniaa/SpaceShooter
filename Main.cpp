#include <SFML/Graphics.hpp>
#include "GameManager.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode({750,950}),"Space Shooter");
	sf::Clock clock;
	GameManager gamaManager(window);
	while(window.isOpen())
	{
		float delta = clock.restart().asSeconds();
		while(const auto Event = window.pollEvent())
		{
			if(Event->is<sf::Event::Closed>())
			{
				window.close();
			}
			gamaManager.InputHandler(delta,Event);
		}
		
		window.clear();
		gamaManager.Update(delta);
		gamaManager.Draw();
		window.display();
	}
	return 0;
}
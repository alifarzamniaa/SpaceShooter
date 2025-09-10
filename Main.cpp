#include <SFML/Graphics.hpp>
#include "PlayArea.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode({750,950}),"Space Shooter");
	sf::Clock clock;
	PlayArea playArea(window);
	while(window.isOpen())
	{
		float delta = clock.restart().asSeconds();
		while(const auto Event = window.pollEvent())
		{
			if(Event->is<sf::Event::Closed>())
			{
				window.close();
			}
			playArea.InputHandler(delta,Event);
		}
		
		window.clear();
		playArea.Update(delta);
		playArea.Draw();
		window.display();
	}
	return 0;
}
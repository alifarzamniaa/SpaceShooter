#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode({700,900}),"Space Shooter");

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
		window.display();
	}
	return 0;
}
#include <SFML/Graphics.hpp>
#include "HUD.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Alien Shooter");
	window.setFramerateLimit(60);

	Player* player = new Player();
	Monsters* monsters = new Monsters();

	HUD hud(player,monsters);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		hud.update(window);

		window.clear(sf::Color::White);
		hud.draw(window);
		window.display();
	}

	return 0;
}
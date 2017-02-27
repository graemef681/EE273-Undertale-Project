#include <SFML/Graphics.hpp>
#include "Destination.hpp"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "GUI Driver");
	Destination Snowden({75,75}, {50,50});
	Destination Waterfall({ 75,75 }, { 450,450 });

	std::cout << "Distance 1: " << Snowden.distance_from(Waterfall) << std::endl;
	std::cout << "Distance 2: " << Waterfall.distance_from(Snowden) << std::endl;
	//Window event and draw loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(Snowden.Draw());
		window.draw(Waterfall.Draw());
		window.display();
	}

	return 0;
}
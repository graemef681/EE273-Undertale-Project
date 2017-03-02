#pragma once
#include <iostream>
#include <List>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Top.hpp"
using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(250, 250), "GUI Driver");
	list<Destination> Top;
	Top = ReadFile("Node_topology");

	
	//addNewDest("Node_topology",&Top);
	//deleteDest(&Top,"Waterfall","Node_topology");
	Top = ReadFile("Node_topology");
	//Window event and draw loop

	list<Destination>::iterator begin = Top.begin(), end = Top.end(), It, It2;

	It = begin;
	It2 = It++;
	while (It != end)
	{
		cout << It->distance_from(*It2) << endl;
		It++;
	}
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		using namespace std;

		list<Destination>::iterator begin = Top.begin(), end = Top.end(), It;

		It = begin;
		while (It != end)
		{
			window.draw(*It);
			It++;
		}
		window.display();
	}
	
	
	return 0;
}




#pragma once
#include <iostream>
#include <List>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Destination.hpp"


using namespace std;
list<Destination> ReadFile(string filename)
{
start:
	list<Destination> Topology;
	ifstream inFile;
	inFile.open(filename + ".txt");
	if (inFile.is_open())
	{
		while (!inFile.eof())
		{
			string temp;
			string name;
			getline(inFile, name, ';');
			float x;
			getline(inFile, temp, ',');
			x = stof(temp);
			float y;
			getline(inFile, temp, ';');
			y = stof(temp);
			float speed_avg;
			getline(inFile, temp);
			speed_avg = stof(temp);
			Destination D({ 25, 25 }, { x, y }, name, speed_avg);
			Topology.push_back(D);
		}
		inFile.close();
		return Topology;
	}
	else
	{
		cout << "Failed to read file, please try again" << endl;
		cout << "Enter a new filename: ";
		cin >> filename;
		goto start;
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(250, 250), "GUI Driver");
	list<Destination> Top;
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




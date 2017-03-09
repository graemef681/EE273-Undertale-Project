#pragma once
#include <iostream>
#include <List>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Top.hpp"
#include"GUI_functions.hpp"
using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(250, 250), "GUI Driver");
	list<Destination> Top;
	Top.clear();
	Top = ReadFile("Node_topology");

	//addNewDest("Node_topology",&Top);
	//deleteDest(&Top,"Waterfall","Node_topology");


	//Window event and draw loop

	list<Destination>::iterator begin = Top.begin(), end = Top.end(), It, It2;

	It = begin;
	It2 = It++;
	while (It != end)
	{
		cout << It->distance_from(*It2) << endl;
		It++;
	}
	bool selected = false;
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

		//get position of mouse when it is clicked
		bool blInBox = false;
		Destination temp, startDest, endDest;; //instance to return destination clicked on
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				

				cout << "CLICK" << endl;
				sf::Vector2i position = sf::Mouse::getPosition(window);
				//call checkInBox function
				//remember to pass in psotion 
				blInBox = inBox(&Top,position,&temp);
				cout << "blinbox is:" << blInBox << endl;
			}
		}//end of click event
			if (blInBox)
			{
					//if the destination is the first selected
					if (selected == false)
					{
						//set it as the start
						Destination startDest = temp;
						cout << "START DESTINATION SET:"<<startDest.getName() << endl;
						cout << "Selected is" << selected << endl;
						selected = true;
					}
					else
					{
						if (startDest.getName() != temp.getName())
						{
							//otherwise, set it as the end
							Destination endDest = temp;
							cout << "END DESTINATION SET:"<<endDest.getName() << endl;
							cout << "Selected is" << selected << endl;
						}
					}
					//this is where start and end would be put in the pathfinder
			}
			selected = false;
	}//end of window loop
	
	
	return 0;
}




#pragma once
#include <iostream>
#include <List>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Top.hpp"
#include "GUI_functions.hpp"
#include "Dog.hpp"
using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 490), "GUI Driver");
	sf::RectangleShape TopologyBox({ 427,488 });
	Dog dog;
	int i = 0;
	TopologyBox.setPosition({ 1.5,1.5 });
	TopologyBox.setFillColor(sf::Color::Transparent);
	TopologyBox.setOutlineColor(sf::Color::Green);
	TopologyBox.setOutlineThickness(1.5);
	list<Destination> Buttons;
	Destination AddButton({ 75,50 }, { 490,40 }, "AddButton", 0, 0);
	AddButton.setFillColor(sf::Color::Green);
	Destination DelButton({ 75,50 }, { 590,40 }, "DelButton", 0, 0);
	DelButton.setFillColor(sf::Color::Red);
	Buttons.push_back(AddButton);
	Buttons.push_back(DelButton);
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
			//get position of mouse when it is clicked
			bool blInBox = false;
			bool ButtInBox = false;
			Destination temp, startDest, endDest;; //instance to return destination clicked on
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					cout << "CLICK" << endl;
					sf::Vector2i position = sf::Mouse::getPosition(window);
					//call checkInBox function
					//remember to pass in position 
					blInBox = inBox(&Top, position, &temp);
					ButtInBox = inBox(&Buttons, position, &temp);
					cout << "blinbox is:" << blInBox << endl;
					cout << "ButtInBox is: " << ButtInBox << endl;
				}
				if (blInBox)
				{
					//if the destination is the first selected
					if (selected == false)
					{
						//set it as the start
						Destination startDest = temp;
						cout << "START DESTINATION SET:" << startDest.getName() << endl;
						cout << "Selected is" << selected << endl;
						selected = true;
					}
					else
					{
						if (startDest.getName() != temp.getName())
						{
							//otherwise, set it as the end
							Destination endDest = temp;
							cout << "END DESTINATION SET:" << endDest.getName() << endl;
							cout << "Selected is" << selected << endl;
						}
					}
					//this is where start and end would be put in the pathfinder
				}
				if (ButtInBox)
				{
					if (temp.getName() == "AddButton")
					{
						addNewDest("Node_Topology", &Top);
						ReadFile("Node_Topology");
					}
					else if (temp.getName() == "DelButton")
					{
						string nodeToDelete;
						cout << "Please enter the name of the destination you wish to delete: ";
						cin >> nodeToDelete;
						deleteDest(&Top, nodeToDelete, "Node_Topology");
					}
				}
			}//end of click event
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
		list<Destination>::iterator Bbegin = Buttons.begin(), Bend = Buttons.end(), Bit;
		Bit = Bbegin;
		while (Bit != Bend)
		{
			window.draw(*Bit);
			Bit++;
		}
		window.draw(TopologyBox);
		//Dog sprite animation
		if (i < 12000)
			i++;
		else if (i == 12000)
			i = 0;
		window.draw(dog.Draw(i));
		window.display();
	}//end of window loop
	

	return 0;
}
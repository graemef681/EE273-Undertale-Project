#pragma once
#include <iostream>
#include <List>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Top.hpp"
#include "GUI_functions.hpp"
#include "Dog.hpp"
#include "Walker.hpp"
#include "Bus.hpp"
#include "Train.hpp"
#include "Destination.hpp"
#include <string>
using namespace std;

int main()
{
	Destination startDest, endDest;
	sf::RenderWindow window(sf::VideoMode(640, 490), "GUI Driver");
	sf::RectangleShape Background;
	Background.setSize(sf::Vector2f(window.getSize()));
	sf::Texture BackgroundTexture;
	// Let's create the background image here, where everything initializes.
	if (!BackgroundTexture.loadFromFile("background.png"))
		cout << "Texture couldnt be read" << endl;
	else
		Background.setTexture(&BackgroundTexture);


	sf::RectangleShape TopologyBox({ 427,490 });
	sf::RectangleShape TopBackground;
	TopBackground.setSize(sf::Vector2f(TopologyBox.getSize()));
	sf::Texture TopTexture;
	if (!TopTexture.loadFromFile("topbackground.png"))
		cout << "Texture couldnt be read" << endl;
	else
		TopBackground.setTexture(&TopTexture);


	TopologyBox.setPosition({ 0,0 });
	TopologyBox.setFillColor(sf::Color::Transparent);
	TopologyBox.setOutlineColor(sf::Color::Black);
	TopologyBox.setOutlineThickness(3);
	list<Destination> Buttons;
	Destination AddButton({ 75,50 }, { 480,60 }, "AddButton", 0, 0);
	AddButton.setFillColor(sf::Color::Green);
	Destination DelButton({ 75,50 }, { 580,60 }, "DelButton", 0, 0);
	DelButton.setFillColor(sf::Color::Red);
	Destination WalkButton({ 75,75 }, { 530,210 }, "WalkButton", 0, 0);
	WalkButton.setFillColor(sf::Color::Yellow);
	Destination BusButton({ 75,75 }, { 530,285 }, "BusButton", 0, 0);
	BusButton.setFillColor(sf::Color::Blue);
	Destination TrainButton({ 75,75 }, { 530,360 }, "TrainButton", 0, 0);
	TrainButton.setFillColor(sf::Color::Magenta);
	Buttons.push_back(WalkButton);
	Buttons.push_back(BusButton);
	Buttons.push_back(TrainButton);
	Buttons.push_back(AddButton);
	Buttons.push_back(DelButton);

	Dog dog;
	int i = 0, mode = 0;

	list<Destination> Top;
	Top.clear();
	Top = ReadFile("Node_topology");

	sf::Texture nodeTexture;
	if (!nodeTexture.loadFromFile("node.png"))
		cout << "Texture couldnt be read" << endl;
	//Window event and draw loop


	bool selected = false;
	bool adding = false;
	bool deleting = false;
	while (window.isOpen())
	{
		list<Destination>::iterator It;
		It = Top.begin();
		while (It != Top.end())
		{
			It->setTexture(&nodeTexture);
			It++;
		}
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			//get position of mouse when it is clicked
			bool blInBox = false;
			bool ButtInBox = false;
			Destination temp; //instance to return destination clicked on
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
						startDest = temp;
						cout << "START DESTINATION SET:" << startDest.getName() << endl;
						cout << "Selected is" << selected << endl;
						selected = true;
					}
					else
					{
						if (startDest.getName() != temp.getName())
						{
							//otherwise, set it as the end
							endDest = temp;
							cout << "START DESTINATION SET:" << startDest.getName() << endl;
							cout << "END DESTINATION SET:" << endDest.getName() << endl;
							cout << "Selected is" << selected << endl;

							//********** GOING TO NEED SOME KIND OF CONDITION HERE 
							//********** TO CHANGE WHETHER BUS, WALKER OR TRAIN IS USED
							//**********Later on this can be switched to on a button press
							string transportType, avoidName;
							cout << "How would you like to travel? (Bus/Walking/Train) :" << endl;
							cin >> transportType;
							
							char cLeaveAfter='n', cArriveBefore='n', cAvoid='n', cStops = 'n';
							cout << "Do you want to select a time to leave after?" << endl;
							cin >> cLeaveAfter;

							if (cLeaveAfter == 'n')
							{
								//leaveAfter and arrive before can't both be called at once 
								cout << "Do you want to select a time to arrive before?" << endl;
								cin >> cArriveBefore;
							}
							
							cout << "Do you want to avoid any destinations?" << endl;
							cin >> cAvoid;

							if (cAvoid == 'y')
							{
								cout << "Please enter the name of the destination to avoid:" << endl;
								cin >> avoidName;
							}

							cout << "Do you want to minimise the number of stops?" << endl;
							cin >> cStops;

							//Call appropriate pathfinding function
							Travel pathfinder;
							double distance, time;
							if (cStops == 'y'&& cAvoid =='n')
							{
								//distance = pathfinder.pathfinding_algorithm(&startDest, &endDest, &Top,cStops);
							}
							else if (cAvoid=='y'&& cStops =='n')
							{
								distance = pathfinder.pathfinding_algorithm(&startDest, &endDest, &Top, avoidName);
							}
							else if (cStops == 'y' && cAvoid == 'y')
							{
							//	distance = pathfinder.pathfinding_algorithm(&startDest, &endDest, &Top, cStops, avoidName);
							}
							else
							{
								// call the basic pathfinding function
								cout << "BASIC PATHFINDING CALLED";
								distance = pathfinder.pathfinding_algorithm(&startDest, &endDest, &Top);
							}
							//Calculate the journey time from the correct mode 
							if (transportType == "Train")
							{
								Train test;
								time=test.calcJourneyTime(distance);
							}
							else if (transportType == "Bus")
							{
								Bus test;
								time = test.calcJourneyTime(distance);
							}
							else if (transportType == "Walker")
							{
								Walker test;
								time = test.calcJourneyTime(distance);
							}
							else
							{
								std::cout << "Error: No Transport type in main" << std::endl;
							}
							//Check arriveBefore and leaveAfter
							if (cLeaveAfter == 'y')
							{
								pathfinder.leaveAfter(time);
							}
							else if (cArriveBefore == 'y')
							{
								pathfinder.arriveBefore(time);
							}
							else
							{
								//calculate total journey time if the left now (including wait when it comes to train/bus)
								pathfinder.leaveAfter(time);
							}

						}
					}
					//this is where start and end would be put in the pathfinder
				}
				if (ButtInBox)
				{						
					if (temp.getName() == "AddButton" && deleting != true)
					{
						cout << "\n\n\nAdd button pressed" << endl;
						adding = true;
						OpenAddWindow();
						addNewDest("Node_Topology", &Top);
						Top.clear();
						Top = ReadFile("Node_Topology");
						cout << "File read." << endl;
					}
					else if (temp.getName() == "DelButton" && adding != true)
					{
						deleting = true;
					}
					else if (temp.getName() == "WalkButton")
					{
						mode = 0; cout << "Mode is: " << mode << endl;
					}
					else if (temp.getName() == "BusButton")
					{
						mode = 1; cout << "Mode is: " << mode << endl;
					}
					else if (temp.getName() == "TrainButton")
					{
						mode = 2; cout << "Mode is: " << mode << endl;
					}
				}
				if (deleting)
				{
					cout << "Temp Name: " << temp.getName() << endl;
					cout << "Click the destination you want to delete!\n";
					list<Destination>::iterator TBegin = Top.begin(), Tend = Top.end();
					It = Tend;
					while (It != TBegin)
					{
						It--;
						cout << "It->getName(): " << It->getName() << endl;
						if (It->getName() == temp.getName())
						{
							deleteDest(&Top, temp.getName(), "Node_topology");
							deleting = false;
							break;
						}
						
					}
				}
			}//end of click event
		}

		window.clear();
		window.draw(Background);
		window.draw(TopBackground);
		
		It = Top.begin();
		while (It != Top.end())
		{

			window.draw(*It);
			It++;
		}
		list<Destination>::iterator Bit;
		Bit = Buttons.begin();
		while (Bit != Buttons.end())
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
	
	Top.clear();
	return 0;
}
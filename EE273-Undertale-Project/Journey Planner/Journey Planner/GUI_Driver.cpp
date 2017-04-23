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
	window.setFramerateLimit(60);
	sf::RectangleShape Background;
	Background.setSize(sf::Vector2f(window.getSize()));
	sf::Texture BackgroundTexture;
	// set background to buttons section here
	if (!BackgroundTexture.loadFromFile("background.png"))
		cout << "Texture couldnt be read" << endl;
	else
		Background.setTexture(&BackgroundTexture);

	//set grid background to topology
	sf::RectangleShape TopologyBox({ 427,490 });
	sf::RectangleShape TopBackground;
	TopBackground.setSize(sf::Vector2f(TopologyBox.getSize()));
	sf::Texture TopTexture;
	if (!TopTexture.loadFromFile("topbackground.png"))
		cout << "Texture couldnt be read" << endl;
	else
		TopBackground.setTexture(&TopTexture);

	//create buttons
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

	//create dog animation in corner
	Dog dog;

	//read in the topology
	list<Destination> Top;
	Top.clear();
	Top = ReadFile("Node_topology");

	//set the texture for the nodes
	sf::Texture nodeTexture;
	if (!nodeTexture.loadFromFile("node.png"))
		cout << "Texture couldnt be read" << endl;

	//initialise booleans for buttons
	bool selected = false;
	bool adding = false;
	bool deleting = false;

	//Instructions for user pt1
	cout << "Welcome to the journey planner!\n To begin, please select a mode of transport using the buttons on the right \n(Walking: Yellow Button\n Bus: Blue Button\n Train: Pink Button)" << endl;
	

	int i = 0, mode = 0;
	//Initialise walking mode and int animation iterator
	//Window event and draw loop
	while (window.isOpen())
	{
		//draw all of the destinations to the screen
		list<Destination>::iterator It;
		It = Top.begin();
		while (It != Top.end())
		{
			It->setTexture(&nodeTexture);
			It++;
		}
		//check for events
		sf::Event event;
		while (window.pollEvent(event))
		{
			//if close button is pressed, window is closed
			if (event.type == sf::Event::Closed)
				window.close();
			//get position of mouse when it is clicked
			bool blInBox = false;
			bool ButtInBox = false;
			char correctSelect;
			Destination temp; //instance to return destination clicked on
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i position = sf::Mouse::getPosition(window);
					//call checkInBox function
					//checks if the user has clicked a button or node
					blInBox = inBox(&Top, position, &temp);
					ButtInBox = inBox(&Buttons, position, &temp);
				}
				if (blInBox)
				{
					//if the destination is the first selected
					if (selected == false)
					{
						//set it as the start
						startDest = temp;
						cout << "Now please select your end destination." << endl;//user instructions pt3
						selected = true;
					}
					else
					{
						if (startDest.getName() != temp.getName())
						{
							//otherwise, set it as the end
							endDest = temp;
							selected = false; //reset selected so the user can select another start/end
							cout << "START DESTINATION:" << startDest.getName() << endl;
							cout << "END DESTINATION:" << endDest.getName() << endl;
							cout << "Are these the start and end destinations that you want? (y/n):";
							cin >> correctSelect;

							if (correctSelect == 'n')
							{
								cout << "\nPlease select a start destination." << endl;
								break;
							}

							string transportType, avoidName;
							switch (mode)
							{
							case 0: transportType = "Walker"; break;
							case 1: transportType = "Bus"; break;
							case 2: transportType = "Train"; break;
							}

							char cLeaveAfter = 'n', cArriveBefore = 'n', cAvoid = 'n';
							cout << "Do you want to select a time to leave after? (y/n): ";
							cin >> cLeaveAfter;

							if (cLeaveAfter == 'n')
							{
								//leaveAfter and arrive before can't both be called at once 
								cout << "Do you want to select a time to arrive before? (y/n): ";
								cin >> cArriveBefore;
							}

							cout << "Do you want to avoid any destinations? (y/n): ";
							cin >> cAvoid;

							if (cAvoid == 'y')
							{
								bool sameName = false;
								do
								{
									cout << "Please enter the name of the destination to avoid: ";
									cin >> avoidName;
									if (avoidName == startDest.getName() || avoidName == endDest.getName())
									{
										sameName = true;
										cout << "You cannot avoid the start/end destination." << endl;
									}
									else
									{
										sameName = false;
									}
								}
								while (sameName);
							}

							//Call appropriate pathfinding function
							Travel pathfinder;
							double distance, time;
						
						    if (cAvoid == 'y')
							{
								distance = pathfinder.pathfinding_algorithm(&startDest, &endDest, &Top, avoidName);
							}
							else
							{
								// call the basic pathfinding function
								distance = pathfinder.pathfinding_algorithm(&startDest, &endDest, &Top);
							}
							//Calculate the journey time from the correct mode 
							switch (mode)
							{
							case 0:
							{
								Walker test;
								time = test.calcJourneyTime(distance);
								break;
							}
							case 1:
							{
								Bus test;
								time = test.calcJourneyTime(distance);
								break;
							}
							case 2:
							{
								Train test;
								time = test.calcJourneyTime(distance);
								break;
							}
							}
							//Check arriveBefore and leaveAfter
							if (cLeaveAfter == 'y')
							{
								switch (mode)
								{
								case 0:
								{
									cout << "Your total journey time is: " << time << ", and you can leave any time you want." << endl;
									break;
								}
								case 1:
								{
									Bus test;
									test.leaveAfter(time);
									break;
								}
								case 2:
								{
									Train test;
									test.leaveAfter(time);
									break;
								}
								default:
								{
									cout << "Error: No appropriate mode set" << endl;
								}
								}

							}
							else if (cArriveBefore == 'y')
							{
								if (transportType == "Train")
								{
									Train test;
									test.arriveBefore(time);
								}
								else if (transportType == "Bus")
								{
									Bus test;
									test.arriveBefore(time);
								}
								else if (transportType == "Walker")
								{
									Walker test;
									test.arriveBefore(time);
								}
								else
								{
									std::cout << "Error: No Transport type in main" << std::endl;
								}

							}
							else
							{
								//calculate total journey time if the left now (including wait when it comes to train/bus)
								if (transportType == "Train")
								{
									Train test;
									test.leaveNow(time);
								}
								else if (transportType == "Bus")
								{
									Bus test;
									test.leaveNow(time);
								}
								else if (transportType == "Walker")
								{
									cout << "Your total journey time is: " << time << ", and you can leave any time you want." << endl;
								}
								else
								{
									std::cout << "Error: No Transport type in main" << std::endl;
								}
							}

						}
						else if (startDest.getName() == temp.getName())
						{
							cout << "The end destination cannot be the same as the start destination, please select another destination." << endl;
						}
						//user instructions pt4
						cout << "If you would like to plan another journey, please start again by selecting your mode of transport using the buttons on the right\n (Walking: Yellow Button\n Bus: Blue Button\n Train: Pink Button)" << endl;
						cout << "Alternatively, if you would like to use the same mode of transport, please select your start destination." << endl;
					}
				}
				if (ButtInBox)
				{
					if (temp.getName() == "AddButton" && deleting != true)
					{//if the user has pressed the add node button
						adding = true;
						OpenAddWindow();
						//Optional call function to add node from console
						//refresh topology so new node is incuded 
						Top.clear();
						Top = ReadFile("Node_Topology");
					}
					else if (temp.getName() == "DelButton" && adding != true)
					{//delete button has been pressed
						deleting = true;
					}
					else if (temp.getName() == "WalkButton")
					{//walk button has been pressed
						mode = 0;
						cout << "Next, please select your starting destination." << endl; //user instructions pt2 
					}
					else if (temp.getName() == "BusButton")
					{//bus button has been pressed
						mode = 1; cout << "Mode is: Bus" << endl;
						cout << "Next, please select your starting destination." << endl;//user instructions pt2 
					}
					else if (temp.getName() == "TrainButton")
					{//train button has been pressed 
						mode = 2; cout << "Mode is: Train" << endl;
						cout << "Next, please select your starting destination." << endl; //user instructions pt2
					}
				}
				if (deleting)
				{//if the user clicked deleted
					cout << "Click the destination you want to delete!\n";
					//delete the node the user clicks on
					list<Destination>::iterator TBegin = Top.begin(), Tend = Top.end();
					It = Tend;
					while (It != TBegin)
					{
						It--;
						if (It->getName() == temp.getName())
						{//find the node the user wants to delete and remove it
							deleteDest(&Top, temp.getName(), "Node_topology");
							deleting = false;
							break;
						}

					}
				}
			}//end of click event
		}//end of check event loop

		 //clear window and draw backgrounds
		window.clear();
		window.draw(Background);
		window.draw(TopBackground);

		It = Top.begin();
		while (It != Top.end())
		{
			//draw nodes
			window.draw(*It);
			It++;
		}
		list<Destination>::iterator Bit;
		Bit = Buttons.begin();
		while (Bit != Buttons.end())
		{//draw buttons
			window.draw(*Bit);
			Bit++;
		}
		window.draw(TopologyBox);
		//Dog sprite animation
		if (i < 100)
			i++;
		else if (i == 100)
			i = 0;
		window.draw(dog.Draw(i));
		window.display();
	}//end of window loop

	Top.clear();
	return 0;
}
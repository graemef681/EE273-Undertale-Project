#include"GUI_functions.hpp"
#include "Top.hpp"
using namespace std;

bool inBox(list<Destination>* top, sf::Vector2i position, Destination* temp)
{
	list<Destination>::iterator begin = (*top).begin(), end = (*top).end(), It;
	It = begin;
	//check if the mouse click is on any of the squares 
	bool inBox = false;
	while (It != end)
	{
		sf::Vector2f curDest;
		float curX, curY, xmin, xmax, ymin, ymax;
		//get position of the centre of the destination
		curDest = It->getPosition();
		//split into x and y components and define size of box
		curX = position.x;
		curY = position.y;
		xmin = curDest.x - (It->getSize().x / 2);
		xmax = curDest.x + (It->getSize().x / 2);
		ymin = curDest.y - (It->getSize().y / 2);
		ymax = curDest.y + (It->getSize().y / 2);
		//if the mouse is in a box
		if (curX >= xmin && curX <= xmax && curY >= ymin && curY <= ymax)
		{
			//set in box to true
			inBox = true;
			*temp = *It;
			break;
		}
		else
		{
			inBox = false;
			It++;
		}
	}//end of list loop

	return inBox;
}

void OpenAddWindow()
{
	sf::RenderWindow window(sf::VideoMode(320, 245), "Add New Destination");
	window.setFramerateLimit(60);
	sf::RectangleShape Background;
	Background.setSize(sf::Vector2f(window.getSize()));
	Background.setPosition({ 0,0 });
	Background.setFillColor(sf::Color::Black);
	string newName, curNeighbour;
	float newX, newY;
	float newSpeed;
	string* neighbours;
	neighbours = new string[0];
	int noNeighbours;
	std::string str;
	int n;
	sf::Font font;
	font.loadFromFile("sansation.ttf"); //Just put it in working directory, should work easier than the pictures c: 

	sf::Text text;
	sf::RectangleShape Textbox;
	sf::Text Caption;
	text.setFont(font);
	Caption.setFont(font);
	Textbox.setSize({ (window.getSize().x / float(1.3)), (window.getSize().y / float(4)) });
	Textbox.setPosition({ (window.getSize().x / float(9)), (window.getSize().y * float(0.5)) });
	text.setPosition({ (window.getSize().x / float(9)), (window.getSize().y * float(0.5)) });
	text.setFillColor(sf::Color::Red);
	Caption.setFillColor(sf::Color::White);
	Caption.setString("Name :");
	int iterator = 0;
	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			switch (event.type)
			{
				// window closed
			case sf::Event::Closed:
			{
				window.close();
				break;
			}
			// In event loop...
			case sf::Event::TextEntered: //en.sfml-dev.org/forums/index.php?topic=2269.0
			{
				// Handle ASCII characters only
				if (event.text.unicode < 128 && event.text.unicode > 31)
				{
					str += static_cast<char>(event.text.unicode);
					text.setString(str);
					if (text.getString().getSize() == 17)
						str = "";
				}
			}
			// key pressed
			case sf::Event::KeyReleased:
			{
				if (event.key.code == sf::Keyboard::Return)
				{
					if (!str.empty())
					{
						//Check text is valid then continue to get next information until all information gathered
						switch (iterator)
						{
						case -1:
							Caption.setString("Name :");
							cout << str << endl; //Set value of last item
							iterator++;
							break;
						case 0:
						{
							Caption.setString("X co-ordinate :");
							newName = str;
							iterator++;
							break;
						}
						case 1:
						{
							try
							{
								newX = stof(str);
								iterator++;
								Caption.setString("Y co-ordinate : ");
							}
							catch (std::exception)
							{
								Caption.setString("X co-ordinate :");
								str = "";
							}
							break;
						}
						case 2:
						{
							try
							{
								newY = stof(str);
								iterator++;
								Caption.setString("Average Speed : ");
							}
							catch (std::exception)
							{
								Caption.setString("Y co-ordinate : ");
								str = "";
							}
							break;
						}
						case 3:
						{
							try
							{
								newSpeed = stof(str);
								iterator++;
								Caption.setString("No. of Neighbours : ");
							}
							catch (std::exception)
							{
								Caption.setString("Average Speed : ");
								str = "";
							}
							break;
						}
						case 4:
						{
							try
							{
								noNeighbours = stof(str);
								neighbours = new string[noNeighbours];
								n = 0;
								Caption.setString("Neighbour #1 :");
								iterator++;
							}
							catch (std::exception)
							{
								Caption.setString("No. of Neighbours : ");
								str = "";
							}
							break;
						}
						default:
						{
							if (n < noNeighbours - 1)
							{
								neighbours[n] = str;
								Caption.setString("Neighbour #" + to_string(n + 2) + " :");
								iterator++;
								n++;
								break;
							}
							else if (n = noNeighbours - 1)
							{
								neighbours[n] = str;
								for (int i = 0; i < noNeighbours; i++)
									cout << neighbours[i] << endl;
								addNewDest("Node_topology", newName, newX, newY, newSpeed, neighbours, noNeighbours);
								window.close();
							}
						}
						}
						str = "";
						text.setString(str);
					}
				}
				if (event.key.code == sf::Keyboard::BackSpace)
				{
					if (!str.empty())
					{
						str.pop_back();
						text.setString(str);
					}

				}
			}
			}
		}
		window.clear();
		window.draw(Background);
		window.draw(Textbox);
		window.draw(text);
		window.draw(Caption);
		window.display();
	}
}
//end of function in box
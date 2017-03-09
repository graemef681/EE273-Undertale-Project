#include"GUI_functions.hpp"
using namespace std;

bool inBox(list<Destination>* top, sf::Vector2i position, Destination* temp)
{
	cout << "called" << endl;
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
		xmin = curDest.x - 12.5;
		xmax = curDest.x + 12.5;
		ymin = curDest.y - 12.5;
		ymax = curDest.y + 12.5;
		//if the mouse is in a box
		if (curX >= xmin && curX<= xmax && curY >=ymin && curY <=ymax)
		{
			cout << "In if" << endl;
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
}//end of function in box

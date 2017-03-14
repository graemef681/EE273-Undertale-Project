#include "Dog.hpp"
#include <iostream>


Dog::Dog()
{
	if (!Spritesheet.loadFromFile("dog.png"))
	{
		std::cout << "Error loading dog spritesheet" << std::endl;
	};

	dogentity.setTexture(Spritesheet);
	dogentity.setTextureRect(sf::IntRect(0, 565, 18, 12));
	dogentity.setPosition({ 400,5 });
}


Dog::~Dog()
{
}


// Annoying Dog sprite animation
sf::Sprite Dog::Draw(int i)
{
	int n;
	n = floor(i / 1000);
	dogentity.setTextureRect(sf::IntRect((n * 18), 565, 18, 12));
	return dogentity;
}

#pragma once
#include <SFML/Graphics.hpp>
class Dog
{
public:
	Dog();
	~Dog();
	// Annoying Dog sprite animation
	sf::Sprite Draw(int);
protected:
	sf::Texture Spritesheet;
	sf::Sprite dogentity;
};


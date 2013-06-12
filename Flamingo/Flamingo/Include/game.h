#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "head.h"

class game 
{
public:
	game(sf::RenderWindow *Window);
	~game();
	void update(sf::Time DeltaTime);
	void draw();
private:
	sf::RenderWindow *window;

	head flamingoHead;


	sf::Vector2f mousePosition, headPosition, headOrigin, crossHair;
	int drag;

	sf::Texture testitexture;
	sf::Sprite testi;

	sf::Texture crosstexture;
	sf::Sprite crosshair;
};

#endif
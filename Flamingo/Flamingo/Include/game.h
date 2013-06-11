#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>

class game 
{
public:
	game(sf::RenderWindow *Window);
	~game();
	void update();
	void draw();
private:
	sf::RenderWindow *window;
	float mouseX, mouseY, headX, headY;
	sf::Vector2f mousePosition, headPosition, headOrigin, crossHair;
	sf::Vector2f testiVektori;
	int drag;

	sf::Texture testitexture;
};

#endif
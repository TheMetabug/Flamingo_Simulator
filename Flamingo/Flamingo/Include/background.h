#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>
#include <iostream>


class background
{
public:
	background(){}
	background(sf::RenderWindow *Window);
	~background();
	void update(sf::Time DeltaTime);
	void draw();

private:
	sf::RenderWindow *window;

	sf::Vector2f waterPosition;

	sf::Texture *waterTexture;
	sf::Sprite water;

};

#endif


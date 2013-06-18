#ifndef NEST_H
#define NEST_H

#include <SFML/Graphics.hpp>
#include <iostream>


class nest
{
public:
	nest(){}
nest(sf::RenderWindow *Window);
~nest();
void update(sf::Time DeltaTime);
void draw();
private:
	sf::RenderWindow *window;

	sf::Vector2f nestPosition, nestOrigin;

	sf::Texture *nestTexture;
	sf::Sprite flamingonest;

	sf::Texture *crossTexture;

};


#endif
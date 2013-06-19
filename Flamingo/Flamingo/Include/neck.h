#ifndef NECK_H
#define NECK_H

#include <SFML/Graphics.hpp>
#include <iostream>

class neck
{
public:
	neck(){}
	neck(sf::RenderWindow *Window);
	~neck();
	void update(float DeltaTime);
	void draw();
private:
	sf::RenderWindow *window;

	sf::Vector2f neckPosition, neckOrigin;

	sf::Texture *neckTexture;
	sf::Sprite flamingoNeck;
	
};



#endif
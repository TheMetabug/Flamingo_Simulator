#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "program.h"

class background
{
public:
	background(){}
	background(sf::RenderWindow *Window);
	~background();
	void update(float DeltaTime);
	void draw(al::viewport* Viewport);

private:
	sf::RenderWindow *window;

	sf::Vector2f m_waterPosition;

	al::texture* m_skyTexture;
	al::sprite m_sky;

	al::texture* m_waterTexture;
	al::sprite m_water;

	al::texture* m_groundTexture;
	al::sprite m_ground;
};

#endif


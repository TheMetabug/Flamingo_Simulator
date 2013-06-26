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
	void update(float DeltaTime);
	void draw();

private:
	sf::RenderWindow *window;

	sf::Vector2f m_waterPosition;

	sf::Texture *m_skyTexture;
	sf::Sprite m_sky;
	sf::Texture *m_waterTexture;
	sf::Sprite m_water;

};

#endif


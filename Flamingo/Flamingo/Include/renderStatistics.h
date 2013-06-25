#ifndef RENDERSTATISTICS_H
#define RENDERSTATISTICS_H

#include <SFML/Graphics.hpp>
#include <iostream>

class renderStatistics
{
public:
	renderStatistics(){}
	renderStatistics(sf::RenderWindow *Window);
	~renderStatistics();
	void update(float DeltaTime);
	void draw();

private:
	sf::RenderWindow *window;

	float fpsCount, fpsFrames, second;
	int	fps;

	sf::Text *text;
	sf::Font *font;
};

#endif
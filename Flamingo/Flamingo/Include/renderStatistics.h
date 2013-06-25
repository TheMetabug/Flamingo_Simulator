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
	void update(sf::Time dt);
	void draw();

private:
	sf::RenderWindow *window;

	double fpsCount, fpsFrames, second, prevFrame;
	int	fps;

	sf::Text *text;
	sf::Font *font;
};

#endif
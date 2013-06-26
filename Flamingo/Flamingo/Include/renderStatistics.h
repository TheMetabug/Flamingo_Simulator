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

	double m_fpsCount, m_fpsFrames, m_second, m_prevFrame;
	int	m_fps;

	sf::Text *text;
	sf::Font *font;
};

#endif
#include "renderStatistics.h"

#include <sstream>

renderStatistics::renderStatistics(sf::RenderWindow* Window)
{
	m_fpsCount = 0;
	m_fpsFrames = 0;
	m_prevFrame = 0;
	m_fps = 0;
	m_second = 0;

	window = Window;

	font = new sf::Font();
	font->loadFromFile("Assets/arial.ttf");

	text = new sf::Text("", *font, 25);
	text->setColor(sf::Color::Blue);
	text->setPosition(0, 50);
}

renderStatistics::~renderStatistics()
{
#if _DEBUG
	std::cout<<"deleted renderStatistics"<<std::endl;
#endif
	delete text;
	delete font;
}

void renderStatistics::update(sf::Time dt)
{
	double DeltaTime = dt.asMicroseconds() / 1000000.0;
	m_fpsFrames++;
	m_fpsCount += DeltaTime;
	m_second += DeltaTime;
	
	//std::cout<<fps<<std::endl;
	
	if(m_second > 1.0f)
	{
	m_fps = (int)((m_fpsFrames - m_prevFrame) / m_second);
	m_prevFrame = m_fpsFrames;
	text->setString("FPS " + std::to_string((long double)m_fps));
	m_second -= 1.0f;
	}
}

void renderStatistics::draw()
{
	window->draw(*text);
}
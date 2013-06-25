#include "renderStatistics.h"

#include <sstream>

renderStatistics::renderStatistics(sf::RenderWindow* Window)
{
	fpsCount = 0;
	fpsFrames = 0;
	fps = 0;
	second = 0;

	window = Window;

	font = new sf::Font();
	font->loadFromFile("Assets/arial.ttf");
	text = new sf::Text("", *font, 25);

	text->setColor(sf::Color::Blue);
	text->setPosition(0, 50);
}

renderStatistics::~renderStatistics()
{
	std::cout<<"deleted renderStatistics"<<std::endl;
	delete text;
	delete font;
}

void renderStatistics::update(float DeltaTime)
{
	
	fpsCount += DeltaTime;
	second += DeltaTime;
	fps = fpsFrames / fpsCount;
	std::cout<<fps<<std::endl;
	
	if(second > 1.0f)
	{
	text->setString("FPS " + std::to_string((long double)fps));
	second -= 1.0f;
	}
}

void renderStatistics::draw()
{
	fpsFrames++;
	window->draw(*text);
}
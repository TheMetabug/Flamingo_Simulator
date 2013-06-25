#include "renderStatistics.h"

#include <sstream>

renderStatistics::renderStatistics(sf::RenderWindow* Window)
{
	fpsCount = 0;
	fpsFrames = 0;
	prevFrame = 0;
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
	fpsFrames++;
	fpsCount += DeltaTime;
	second += DeltaTime;
	
	//std::cout<<fps<<std::endl;
	
	if(second > 1.0f)
	{
	fps = (fpsFrames - prevFrame) / second;
	prevFrame = fpsFrames;
	text->setString("FPS " + std::to_string((long double)fps));
	second -= 1.0f;
	}
}

void renderStatistics::draw()
{

	window->draw(*text);
}
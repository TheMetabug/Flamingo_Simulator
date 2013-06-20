#include "background.h"

background::background(sf::RenderWindow *Window)				
{
	window = Window;

	waterTexture = new sf::Texture();
	waterTexture->loadFromFile("Assets/waterpuddle.png");
	waterTexture->setSmooth(true);
	water.setTexture(*waterTexture);
	water.setPosition(768, 465);
	water.setOrigin(sf::Vector2f(512, 256));

	skyTexture = new sf::Texture();
	skyTexture->loadFromFile("Assets/skyplaceholder.png");
	skyTexture->setSmooth(true);
	sky.setTexture(*skyTexture);
	sky.setPosition(0, 0);
	sky.setOrigin(sf::Vector2f(0, 0));
}

background::~background()
{
	std::cout<<"deleted background"<<std::endl;
}

void background::update(float DeltaTime)
{
	//water.setPosition(100,100);
}

void background::draw()	
{
	window->draw(sky);
	window->draw(water);
	
}
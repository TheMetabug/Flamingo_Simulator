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
}

background::~background()
{

}
void background::update(float DeltaTime)
{
	//water.setPosition(100,100);
}
void background::draw()	
{
	window->draw(water);
}
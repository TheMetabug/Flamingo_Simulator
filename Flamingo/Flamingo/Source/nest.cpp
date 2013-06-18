#include "nest.h"

nest::nest(sf::RenderWindow *Window)
{
	window = Window;
	nestTexture = new sf::Texture();
	nestTexture->loadFromFile("Assets/NEST.png");
	nestTexture->setSmooth(true);
	flamingonest.setTexture(*nestTexture);
	flamingonest.setPosition(300, 500);
	flamingonest.setOrigin(sf::Vector2f(178.5f, 104));
	flamingonest.setScale(1,1);
}
nest::~nest()
{

}
void nest::update(sf::Time DeltaTime)
{

}
void nest::draw()
{
	window->draw(flamingonest);
}
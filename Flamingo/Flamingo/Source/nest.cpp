#include "nest.h"

nest::nest(sf::RenderWindow *Window, collision* Collide)
{
	nestPosition = sf::Vector2f(200, 600);
	window = Window;
	nestTexture = new sf::Texture();
	nestTexture->loadFromFile("Assets/NEST.png");
	nestTexture->setSmooth(true);
	flamingonest.setTexture(*nestTexture);
	flamingonest.setPosition(nestPosition);
	flamingonest.setOrigin(sf::Vector2f(flamingonest.getLocalBounds().width/2,flamingonest.getLocalBounds().height/2));
	flamingonest.setScale(1,1);

	nestHitbox = Collide->createHitBox(nestPosition,
		sf::Vector2f(flamingonest.getGlobalBounds().width,
					 flamingonest.getGlobalBounds().height), 
		sf::Vector2f(flamingonest.getGlobalBounds().width/2,
					 flamingonest.getGlobalBounds().height/2),
		0);
}
nest::~nest()
{
	std::cout<<"deleted nest"<<std::endl;
}
void nest::update(float DeltaTime)
{
	nestHitbox->Position = nestPosition;
}
void nest::draw()
{
	window->draw(flamingonest);
}
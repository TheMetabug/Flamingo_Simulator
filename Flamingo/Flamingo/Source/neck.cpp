#include "neck.h"
neck::neck(sf::RenderWindow *Window)
{
	window = Window;
	
	neckOrigin.x = 740;
	neckOrigin.y = 550;

	neckTexture = new sf::Texture();
	neckTexture->loadFromFile("Assets/FlamingoEmo_Neck.png");
	neckTexture->setSmooth(true);
	flamingoNeck.setTexture(*neckTexture);
	flamingoNeck.setPosition(neckOrigin);
	flamingoNeck.setOrigin(sf::Vector2f(302, 774));
	flamingoNeck.setScale(0.3f, 0.3f);
	


}

neck::~neck()
{
}

void neck::update(float DeltaTime)
{
}

void neck::draw()
{
	window->draw(flamingoNeck);
	
}
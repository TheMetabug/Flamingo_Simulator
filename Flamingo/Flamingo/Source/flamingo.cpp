#include "flamingo.h"

body::body(sf::RenderWindow *Window)
{
	window = Window;
	bodyOrigin.x = 740;
	bodyOrigin.y = 560;

	bodyTexture = new sf::Texture();
	bodyTexture->loadFromFile("Assets/FlamingoEmo_Body.png");
	bodyTexture->setSmooth(true);
	flamingoBody.setTexture(*bodyTexture);
	flamingoBody.setPosition(bodyOrigin);
	flamingoBody.setOrigin(sf::Vector2f(612, 612));
	flamingoBody.setScale(0.3f, 0.3f);

}

body::~body()
{
}

void body::update(float DeltaTime)
{

}

void body::draw()
{
	window->draw(flamingoBody);
}
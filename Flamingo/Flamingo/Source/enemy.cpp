#include "enemy.h"

enemy::enemy(sf::RenderWindow *Window)
{
	window = Window;

	
	enemyRotate = 5;
	enemyOrigin.x = 350;
	enemyOrigin.y = 100;

	enemyTexture = new sf::Texture();
	enemyTexture->loadFromFile("Assets/enemyplaceholder.png");
	enemyTexture->setSmooth(true);
	enemyBird.setTexture(*enemyTexture);
	enemyBird.setPosition(enemyOrigin);
	enemyBird.setOrigin(sf::Vector2f(128,128));
	enemyBird.setScale(0.5f, 0.5f);


}

enemy::~enemy()
{
}

void enemy::update(sf::Time DeltaTime)
{
	enemyRotate += DeltaTime.asMilliseconds()/10;
	//enemyBird.setPosition(enemyBirdPosition);
	enemyBird.setRotation(enemyRotate);

}

void enemy::draw()
{
	window->draw(enemyBird);
}
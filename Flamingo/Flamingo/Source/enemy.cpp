#include "enemy.h"

enemy::enemy(sf::RenderWindow *Window)
{
	window = Window;

	enemyRotate = 5;
	enemyOrigin.x = 350;
	enemyOrigin.y = 100;

	enemyTexture = new sf::Texture();
	enemyTexture->loadFromFile("Assets/enemyAnimation.png");
	enemyTexture->setSmooth(true);
	enemyBird = new sf::Sprite();
	enemyBird->setTexture(*enemyTexture);
	enemyBird->setPosition(enemyOrigin);
	enemyBird->setOrigin(sf::Vector2f(128,128));
	enemyBird->setScale(0.5f, 0.5f);

	Animator = new animation(enemyBird, 4, 256, 256);

}

enemy::~enemy()
{
	std::cout<<"deleted enemy"<<std::endl;
	delete Animator;
}

void enemy::update(float DeltaTime)
{
	Animator->update(DeltaTime);
	enemyRotate += DeltaTime*100;
	//enemyBird.setPosition(enemyBirdPosition);
	enemyBird->setRotation(enemyRotate);

}

void enemy::draw()
{
	window->draw(*enemyBird);
}
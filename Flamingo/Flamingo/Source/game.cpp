#include "game.h"

game::game(sf::RenderWindow* Window)
{
	window = Window;
	enemyBird = enemy(window);
	flamingoHead = head(window);
	water = background(window);

}

game::~game()
{
}

void game::update(sf::Time DeltaTime)
{
	flamingoHead.update(DeltaTime);
	water.update(DeltaTime);
	enemyBird.update(DeltaTime);
}

void game::draw()
{
	water.draw();
	flamingoHead.draw();
	enemyBird.draw();
	
}
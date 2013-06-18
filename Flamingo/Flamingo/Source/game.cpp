#include "game.h"

game::game(sf::RenderWindow* Window)
{
	window = Window;
	enemyBird = enemy(window);
	flamingoHead = head(window);
	water = background(window);
	text = new gui(window);
	flamingonest = nest(window);
	
}

game::~game()
{
	delete text;
}

void game::update(sf::Time DeltaTime)
{
	flamingoHead.update(DeltaTime);
	water.update(DeltaTime);
	text->update(DeltaTime);
	enemyBird.update(DeltaTime);
}

void game::draw()
{
	water.draw();
	flamingoHead.draw();
	text->draw();
	enemyBird.draw();
	flamingonest.draw();
}
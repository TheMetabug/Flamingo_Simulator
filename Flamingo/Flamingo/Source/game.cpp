#include "game.h"

game::game(sf::RenderWindow* Window)
{
	window = Window;

	flamingoHead = head(window);
}

game::~game()
{
}

void game::update(sf::Time DeltaTime)
{
	flamingoHead.update(DeltaTime);
}

void game::draw()
{
	flamingoHead.draw();
}
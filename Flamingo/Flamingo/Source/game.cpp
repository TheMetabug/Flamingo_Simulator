#include "game.h"

game::game(sf::RenderWindow* Window)
{
	window = Window;

	// hitbox


	// animation


	// gui
	text = new gui(window);

	// head
	flamingoHead = head(window);

	// nest
	flamingonest = nest(window);

	// enemy
	enemyBird = enemy(window);

	// pickups


	// water
	water = background(window);

	// particles


	
}

game::~game()
{
	delete text;
}

void game::update(sf::Time DeltaTime)
{
	// hitbox


	// animation


	// gui
	text->update(DeltaTime);

	// head
	flamingoHead.update(DeltaTime);

	// nest


	// enemy
	enemyBird.update(DeltaTime);

	// pickups


	// water
	water.update(DeltaTime);

	// particles



}

void game::draw()
{
	// hitbox


	// animation


	// gui
	text->draw();

	// head
	flamingoHead.draw();

	// nest
	flamingonest.draw();

	// enemy
	enemyBird.draw();

	// pickups


	// water
	water.draw();

	// particles



}
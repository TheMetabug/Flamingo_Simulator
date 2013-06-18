#include "game.h"

game::game(sf::RenderWindow* Window)
{
	window = Window;

	// gameStates

	state = Play;



	// hitbox


	// animation


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


	// gui
	text = new gui(window);
	
}

game::~game()
{
	delete text;
}

void game::update(sf::Time DeltaTime)
{
	float deltaTime = DeltaTime.asMicroseconds()/1000000.0f;

	// gameStates

	switch(state)
	{
	case TitleScreen:
		break;
	case Play:

		// hitbox


		// head
		flamingoHead.update(deltaTime);


		// nest


		// enemy
		enemyBird.update(deltaTime);

		// pickups


		// water
		water.update(deltaTime);

		// gui
		text->update(deltaTime);

		break;
	case Menu:
		break;
	case Pause:
		break;
	case Credits:
		break;
	}

	// animation


	// particles


}

void game::draw()
{
	// gameStates

		switch(state)
	{
	case TitleScreen:
		break;
	case Play:

		// water
		water.draw();

		// nest
		flamingonest.draw();

		// hitbox


		// enemy
		enemyBird.draw();

		// pickups


		// head
		flamingoHead.draw();


		// gui
		text->draw();


		break;
	case Menu:
		break;
	case Pause:
		break;
	case Credits:
		break;
	}


	// animation


	// particles

	
}
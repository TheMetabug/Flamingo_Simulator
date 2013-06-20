#include "game.h"

game::game(sf::RenderWindow* Window)
{
	window = Window;

	// gameStates

	state = Play;



	// hitbox
	collide = new collision();

	// animation


	// head
	flamingoHead = flamingo(window, collide);
				   
	//neck		   
	flamingoNeck = flamingo(window, collide);
				   
	//flamingo	   
	flamingoBase = flamingo(window, collide);

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
	std::cout<<"deleted maingame"<<std::endl;
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

		//neck
		flamingoNeck.update(deltaTime);

		//body
		flamingoBase.update(deltaTime);


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

		// flamingo

		flamingoBase.draw();
		//neck
		flamingoNeck.draw();
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
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
	flamingoBase = new flamingo(window, collide);

	// nest
	flamingonest = new nest(window);

	// enemy
	enemyBird = new enemy(window);

	// pickups
	m_pickups = new pickups(window,collide);

	// backGround
	backGround = new background(window);


	// particles


	// gui
	text = new gui(window);
	
}

game::~game()
{
	std::cout<<"deleted maingame"<<std::endl;
	delete flamingoBase;
	delete flamingonest;
	delete enemyBird;
	delete backGround;
	delete m_pickups;
	delete collide;
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

		//flamingo
		flamingoBase->update(deltaTime);


		// nest


		// enemy
		enemyBird->update(deltaTime);

		// pickups
		m_pickups->update(deltaTime);

		// backGround
		backGround->update(deltaTime);

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

		// backGround
		backGround->draw();

		// nest
		flamingonest->draw();


		// enemy
		enemyBird->draw();

		// pickups
		m_pickups->draw();

		// flamingo

		flamingoBase->draw();		


		// gui
		text->draw();

		// hitbox
		collide->DrawHitboxes(window);
		m_pickups->drawHitBoxes();


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
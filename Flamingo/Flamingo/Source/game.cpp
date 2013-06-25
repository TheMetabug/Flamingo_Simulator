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
	flamingonest = new nest(window, collide);

	// enemy
	enemyBird = new enemy(window,collide);

	// pickups
	m_pickups = new pickups(window,collide);

	// backGround
	backGround = new background(window);


	// particles


	// gui
	m_gui = new gui(window);
	
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
	delete m_gui;
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

		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			P_release = true;
		else if (P_release)
		{
			P_release = false;
			state = Pause;
		}
		

		// hitbox

		//flamingo
		flamingoBase->update(deltaTime);


		// nest
		flamingonest->update(deltaTime);

		// enemy
		enemyBird->update(deltaTime);

		// pickups
		m_pickups->update(deltaTime);

		// backGround
		backGround->update(deltaTime);

		// gui
		m_gui->update(deltaTime);

		break;
	case Menu:
		break;
	case Pause:
		m_gui->update(deltaTime);
		m_gui->m_pause = true;

		
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			P_release = true;
		else if (P_release)
		{
			P_release = false;
			state = Play;
			m_gui->m_pause = false;
		}



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
	case Pause:

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
		m_gui->draw();

		// hitbox
		collide->DrawHitboxes(window);
		m_pickups->drawHitBoxes();


		break;
	case Menu:
		break;
	case Credits:
		break;
	}


	// animation


	// particles

	
}
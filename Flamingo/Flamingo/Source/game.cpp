#include "game.h"

game::game(sf::RenderWindow* Window, al::viewport* Viewport)
{
	window = Window;
	m_viewport = Viewport;

	////sound
	m_soundLibrary = new soundLibrary();
	
	// gameStates

	state = TitleScreen;

	// hitbox
	collide = new collision();

	// animation


	// head
	flamingoBase = new flamingo(window, m_soundLibrary, collide);

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
	m_gui = new gui();

	
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
	delete m_soundLibrary;
}

void game::update(float deltaTime)
{
	// gameStates

	switch(state)
	{
	

	case TitleScreen:
		// gui
		m_gui->update(deltaTime);

		m_gui->m_title = true;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			state = Menu;
			m_gui->m_title =false;
		}

	
		break;
	
	case Play:
		
		// show text
		m_gui->m_Play = true;
		
		
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			P_release = true;
		else if (P_release)
		{
			m_soundLibrary->m_musics[0]->pause();
			m_soundLibrary->m_sounds[0]->play();
			P_release = false;
			state = Pause;
		}
		
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::M))
			M_release = true;
		else if (M_release)
		{
			m_soundLibrary->m_musics[0]->pause();
			M_release = false;
			state = Gamemenu;
			m_gui->m_Play = false;
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

		
		
		m_gui->update(deltaTime);
		m_gui->m_menu = true;
		
		//Close all the game texts!
		m_gui->m_Play = false;
		m_gui->m_pause = false;
		
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::M))
			M_release = true;
		else if (M_release)
		{
			M_release = false;
			state = Play;
			m_gui->m_menu = false;
		}

		if(sf::Mouse::getPosition(*window).x > m_gui->m_button->m_position.x  - 48 &&
			sf::Mouse::getPosition(*window).x < m_gui->m_button->m_position.x + 48 &&
			sf::Mouse::getPosition(*window).y > m_gui->m_button->m_position.y - 48 &&
			sf::Mouse::getPosition(*window).y < m_gui->m_button->m_position.y + 48)
		{
			m_gui->m_button->m_animation->ChangeAnimation(1,0,1,100);

			if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				m_soundLibrary->m_musics[0]->play();
				m_gui->m_button->m_animation->ChangeAnimation(2,0,2,100);
				state = Play;
				m_gui->m_menu = false;
			}
		}
		else
			m_gui->m_button->m_animation->ChangeAnimation(0,0,0,100);
		





		break;
	case Pause:
		m_gui->update(deltaTime);
		m_gui->m_pause = true;

		
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			P_release = true;
		else if (P_release)
		{
			m_soundLibrary->m_musics[0]->play();
			P_release = false;
			state = Play;
			m_gui->m_pause = false;
		}
		

		break;
	case Credits:
		break;
	case Options:
		break;
	case Gamemenu:
		m_gui->m_Gmenu = true;
		m_gui->update(deltaTime);


		
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
		// gui
		m_gui->draw(m_viewport);

		break;
	case Play:
	case Pause:

		// backGround
		backGround->draw(m_viewport);

		// nest
		flamingonest->draw(m_viewport);


		// enemy
		enemyBird->draw(m_viewport);

		// pickups
		m_pickups->draw(m_viewport);

		// flamingo

		flamingoBase->draw(m_viewport);		


		// gui
		m_gui->draw(m_viewport);

		// hitbox


		break;
	case Menu:

		// gui
		m_gui->draw(m_viewport);

		break;
	case Credits:
		break;

	case Gamemenu:
		m_gui->draw(m_viewport);
		break;
	}


	// animation


	// particles

	
}

void game::drawDebugInfo()
{
	collide->DrawHitboxes(window);
	m_pickups->drawHitBoxes();
}
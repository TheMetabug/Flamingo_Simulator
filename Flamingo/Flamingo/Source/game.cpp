#include "game.h"
using namespace al;

game::game(sf::RenderWindow* Window, viewport* Viewport)
{
	window = Window;
	m_viewport = Viewport;
	m_input = new input(window);

	////sound
	m_soundLibrary = new soundLibrary();
	
	// gameStates

	state = TitleScreen;

	// hitbox
	collide = new collision();

	// animation


	// head
	flamingoBase = new flamingo(m_soundLibrary, collide, m_input);

	// nest
	flamingonest = new nest(collide);

	// enemy
	enemyBird = new enemy(collide);

	// pickups
	m_pickups = new pickups(collide, flamingonest, enemyBird, flamingoBase);

	// backGround
	backGround = new background();

	//cloud
	m_cloud = new cloud();


	// particles

	// gui
	m_gui = new gui(m_input);

	
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

		if (m_input->isKeyPressed(al::Key::Space))
		{
			state = Menu;
			m_gui->m_title =false;
		}

	
		break;
	
	case Play:
		
		// show text
		m_gui->m_Play = true;

		//if (m_gui->m_button2->isPressed())
		//{
			if(!m_gui->m_button2->isPressed())
			{
				ML_release = true;
			}
			else if (ML_release)
			{
				ML_release = false;
				state = Gamemenu;
		
			}

			
		//}
		//}



		if(!m_input->isKeyPressed(al::Key::Pause))
			P_release = true;
		else if (P_release)
		{
			m_soundLibrary->m_musics[0]->pause();
			m_soundLibrary->m_sounds[0]->play();
			P_release = false;
			state = Pause;
		}
		
		if(!m_input->isKeyPressed(al::Key::Menu))
			M_release = true;
		else if (M_release)
		{
			m_soundLibrary->m_musics[0]->pause();
			M_release = false;
			state = Gamemenu;
			
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

		// cloud
		m_cloud->update(deltaTime);

		// gui
		m_gui->update(deltaTime);

		break;
	
	case Menu:

		m_gui->update(deltaTime);
		m_gui->m_menu = true;
		
		//Close all the game texts!
		m_gui->m_Play = false;
		m_gui->m_pause = false;
		
		if(!m_input->isKeyPressed(al::Key::Menu))
			M_release = true;
		else if (M_release)
		{
			M_release = false;
			state = Play;
			m_gui->m_menu = false;
		}


		/*if(	m_input->getMousePosition().x > m_gui->m_button->m_position.x  - m_gui->m_button->m_sprite.getSize().x/2 &&
			m_input->getMousePosition().x < m_gui->m_button->m_position.x + m_gui->m_button->m_sprite.getSize().x/2 &&
			m_input->getMousePosition().y > m_gui->m_button->m_position.y - m_gui->m_button->m_sprite.getSize().y/2 &&
			m_input->getMousePosition().y < m_gui->m_button->m_position.y + m_gui->m_button->m_sprite.getSize().y/2)
		{
			
			m_gui->m_button->m_animation->ChangeAnimation(1,0,1,100);

			if(m_input->isButtonPressed(al::Button::MouseLeft))
			{
				m_soundLibrary->m_musics[0]->play();
				m_gui->m_button->m_animation->ChangeAnimation(2,0,2,100);
				state = Play;
				m_gui->m_menu = false;
			}
		}
		else
			m_gui->m_button->m_animation->ChangeAnimation(0,0,0,100);*/
		

		//uusi
		if (m_gui->m_button->isPressed())
		{
			m_soundLibrary->m_musics[0]->play();
			state = Play;
			m_gui->m_menu = false;
		}

		


		break;
	case Pause:
		m_gui->update(deltaTime);
		m_gui->m_pause = true;

		
		if(!m_input->isKeyPressed(al::Key::Pause))
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

		//if (m_gui->m_button2->isPressed())
		//{
			
			if(!m_gui->m_button2->isPressed())
			{
				ML_release = true;
			}
			else if (ML_release)
			{
				ML_release = false;
				state = Play;
				m_gui->m_Gmenu = false;
			}
		//}



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
		
		//cloud
		m_cloud->draw(m_viewport);

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
	m_pickups->drawHitBoxes(window);
}
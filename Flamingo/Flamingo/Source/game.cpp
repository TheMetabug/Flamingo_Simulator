#include "game.h"
using namespace al;

game::game(sf::RenderWindow* Window, viewport* Viewport)
	:	window(Window),
		m_viewport(Viewport)
{
	m_muted = false;
	m_input = new input(window);

	////sound
	m_soundLibrary = new soundLibrary();
	m_soundLibrary->m_musics[0]->play();
	
	m_titleCard = new titleCard();
	m_titleCard->draw(Viewport);
}

void game::init()
{

	// gameStates

	state = TitleScreen;

	// gui
	m_gui = new gui(m_input);

	// hitbox
	collide = new collision();

	// animation


	// head
	flamingoBase = new flamingo(m_soundLibrary, collide, m_input);

	// nest
	flamingonest = new nest(collide, m_gui);

	// enemy
	enemyBird = new enemy(collide, m_gui);

	// pickups
	m_pickups = new pickups(collide, flamingonest, enemyBird, flamingoBase, m_soundLibrary);

	// backGround
	backGround = new background();

	//cloud
	m_cloud = new cloud();


	// particles

	// titleCard


		m_ReturnPosition = (vector(640,375));
			m_ReturnTexture = new texture("GameMenu/yesnoMenu.png");
			m_ReturnCheck.setTexture(m_ReturnTexture);
			m_ReturnCheck.setPosition(m_ReturnPosition);
			m_ReturnCheck.setOrigin(vector(m_ReturnCheck.getSize().x/2,
			m_ReturnCheck.getSize().y/2));
			m_ReturnCheck.setScale(1,1);

			m_ReturnCheck.setLayer(300);

			m_GmenuPosition = (vector(640,360));
			m_GmenuTexture = new texture("GameMenu/pausemenu.png");
			m_GMenu.setTexture(m_GmenuTexture);
			m_GMenu.setPosition(m_GmenuPosition);
			m_GMenu.setOrigin(vector(m_GMenu.getSize().x/2,
			m_GMenu.getSize().y/2));
			m_GMenu.setScale(1,1);
			  
			m_GMenu.setLayer(299);

			m_creditsPosition = (vector(640,360));
			m_creditsTexture = new texture("creditsPlaceholder.png");
			m_credits.setTexture(m_creditsTexture);
			m_credits.setPosition(m_creditsPosition);
			m_credits.setOrigin(vector(m_credits.getSize().x/2,
			m_credits.getSize().y/2));
			m_credits.setScale(1,1);

			m_optionsPosition = (vector(640,360));
			m_optionsTexture = new texture("OptionsMenu/options menu.png");
			m_options.setTexture(m_optionsTexture);
			m_options.setPosition(m_optionsPosition);
			m_options.setOrigin(vector(m_options.getSize().x/2,
			m_options.getSize().y/2));
			m_options.setScale(1,1);

			
			m_options.setLayer(299);

			

		// opacity

	m_pauseOpacityTexture.loadTexture("GameMenu/pauseScreenOpacity.png");
	m_pauseOpacitySprite.setTexture(&m_pauseOpacityTexture);
	m_pauseOpacitySprite.setLayer(298);
			
}

game::~game()
{
	std::cout<<"deleted maingame"<<std::endl;
	delete m_input;
	delete flamingoBase;
	delete flamingonest;
	delete enemyBird;
	delete backGround;
	delete m_cloud;
	delete m_pickups;
	delete collide;
	delete m_gui;
	delete m_titleCard;
	delete m_soundLibrary;
	delete m_ReturnTexture;
	delete m_GmenuTexture;
	delete m_creditsTexture;
	delete m_optionsTexture;
	
}

void game::update(float deltaTime)
{
	// gameStates
	if (!m_input->isButtonPressed(al::Button::MouseLeft))
	{
		ML_release = true;
	}

	switch(state)
	{

	case TitleScreen:
		// gui
		m_gui->update(deltaTime);

		m_gui->m_title = true;

		if (m_input->isKeyPressed(al::Key::Space))
		{
			state = Menu;
			/*state = ReturnTitle;*/
			/*state = Credits;*/
			m_gui->m_title =false;
		}
	
		break;
	
	case Play:
		
		// show text
		m_gui->m_Play = true;

		//if (m_gui->m_button2->isPressed())
		//{
			if(m_gui->m_button2->isPressed() && ML_release)
			{
				ML_release = false;
				state = Gamemenu;
			}
			else if(m_gui->m_button3->isPressed() && ML_release)
			{
				ML_release = false;

				if (!m_muted)
				{
					m_muted = true;
					m_soundLibrary->mute(true);
					m_gui->m_button3->setTexture(m_gui->m_buttonTextures[5]);
				}
				else
				{
					m_muted = false;
					m_soundLibrary->mute(false);
					m_gui->m_button3->setTexture(m_gui->m_buttonTextures[0]);
				}
			}
			else if(m_input->isButtonPressed(al::Button::MouseLeft))
			{
				ML_release = false;
			}
			

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
		flamingoBase->update(deltaTime, !ML_release);

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

		// titlecard
		m_titleCard->update(deltaTime);

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
			
			P_release = false;
			state = Play;
			m_gui->m_pause = false;
		}
		
		break;
	case Credits:

		break;
	case Options:
		m_gui->m_Options = true;	
		m_gui->update(deltaTime);

			if(m_gui->m_backbutton->isPressed() && ML_release)
			{
				ML_release = false;
				state = Gamemenu;
				m_gui->m_Options = false;
			}
			else if(m_gui->m_applybutton->isPressed() && ML_release)
			{
				ML_release = false;
				state = Gamemenu;
				m_gui->m_Options = false;
			}
			else if(m_input->isButtonPressed(al::Button::MouseLeft))
			{
				ML_release = false;
			}

			

		break;
	case Gamemenu:
		
		m_gui->m_Gmenu = true;
		
		m_gui->update(deltaTime);

			if(m_gui->m_button2->isPressed() && ML_release)
			{
				ML_release = false;
				state = Play;
				m_gui->m_Gmenu = false;
			}
			else if(m_gui->m_Gmenubutton1->isPressed() && ML_release)
			{
				ML_release = false;
				state = Play;
				
				m_gui->m_Gmenu = false;
			}
			else if(m_gui->m_Gmenubutton3->isPressed() && ML_release)
			{
				ML_release = false;
				state = Options;
				m_gui->m_Gmenu = false;
			}
			else if(m_gui->m_Gmenubutton4->isPressed() && ML_release)
			{
				ML_release = false;
				state = ReturnTitle;
				m_gui->m_Gmenu = false;
			}
			else if(m_input->isButtonPressed(al::Button::MouseLeft))
			{
				ML_release = false;
			}


		break;
		case ReturnTitle:
			m_gui->update(deltaTime);
			m_gui->m_returnTitle = true;

			if(m_gui->m_yesbutton->isPressed() && ML_release)
			{
				ML_release = false;
				state = Menu;
				
				m_gui->m_returnTitle = false;
			}
			else if(m_gui->m_nobutton->isPressed() && ML_release)
			{
				ML_release = false;
				state = Gamemenu;
				
				m_gui->m_returnTitle = false;
			}
			else if(m_input->isButtonPressed(al::Button::MouseLeft))
			{
				ML_release = false;
			}
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
		// titlecard
		m_titleCard->draw(m_viewport);
		// gui
		m_gui->draw(m_viewport);

		break;
	
	case ReturnTitle:
		m_viewport->draw(&m_ReturnCheck);
		
	
	case Gamemenu:
		m_viewport->draw(&m_GMenu);
	case Options:
		if (m_gui->m_Options)
		{
			m_viewport->draw(&m_options);
		}

	case Pause:
	
	case Play:
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

		if(m_gui->m_pause == true || m_gui->m_Gmenu == true )
		{
			// pauseopacity
			m_viewport->draw(&m_pauseOpacitySprite);
		}

		// gui
		m_gui->draw(m_viewport);


		// hitbox


		break;
	case Menu:

		// gui
		m_titleCard->draw(m_viewport);
		m_gui->draw(m_viewport);

		break;
	case Credits:
		m_viewport->draw(&m_credits);
		break;


	}


	// animation


	// particles

	
}

void game::drawDebugInfo(sf::RenderWindow *window)
{
	collide->DrawHitboxes(window);
	m_pickups->drawHitBoxes(window);
}

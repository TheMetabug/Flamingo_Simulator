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
game::~game()
{
#if _DEBUG
	std::cout<<"deleted maingame"<<std::endl;
#endif
	delete m_input;
	delete m_flamingo;
	delete m_nest;
	delete m_enemy;
	delete m_background;
	delete m_pickups;
	delete collide;
	delete m_gui;
	delete m_titleCard;
	delete m_soundLibrary;
	delete m_ReturnTexture;
	delete m_GmenuTexture;
	delete m_scoreTexture;
	delete m_creditsTexture;
	delete m_optionsTexture;
	delete m_particleEngine;
	delete m_logoTexture;
	
}

void game::init()
{
	
	// particles
	m_particleEngine = new particleEngine();

	// gameStates

	m_state = TitleScreen;

	// gui
	m_gui = new gui(m_input, m_soundLibrary);

	// hitbox
	collide = new collision();

	// animation


	// head
	m_flamingo = new flamingo(m_soundLibrary, collide, m_input, m_particleEngine);

	// nest
	m_nest = new nest(collide, m_gui, m_particleEngine);

	// enemy
	m_enemy = new enemy(collide, m_gui, m_particleEngine);

	// pickups
	m_pickups = new pickups(collide, m_nest, m_enemy, m_flamingo, m_soundLibrary, m_particleEngine);

	// backGround
	m_background = new background();


	// titleCard

			m_logoPosition = vector(640, 580);
			m_logoTexture = new texture("nameLogo.png");
			m_logoSprite.setTexture(m_logoTexture);
			m_logoSprite.setPosition(m_logoPosition);
			m_logoSprite.setOrigin(vector(m_logoSprite.getSize().x/2, m_logoSprite.getSize().y/2));
			m_logoSprite.setScale(1,1);
			//m_logoSprite.setLayer(299);

			m_ReturnPosition = (vector(640,375));
			m_ReturnTexture = new texture("GameMenu/yesnoMenu.png");
			m_ReturnCheck.setTexture(m_ReturnTexture);
			m_ReturnCheck.setPosition(m_ReturnPosition);
			m_ReturnCheck.setOrigin(vector(m_ReturnCheck.getSize().x/2,
			m_ReturnCheck.getSize().y/2));
			m_ReturnCheck.setScale(1,1);

			m_ReturnCheck.setLayer(299);

			m_GmenuPosition = (vector(640,360));
			m_GmenuTexture = new texture("GameMenu/pausemenu.png");
			m_GMenu.setTexture(m_GmenuTexture);
			m_GMenu.setPosition(m_GmenuPosition);
			m_GMenu.setOrigin(vector(m_GMenu.getSize().x/2,
			m_GMenu.getSize().y/2));
			m_GMenu.setScale(1,1);
			  
			m_GMenu.setLayer(298);

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

			m_scorePosition = (vector(115,59));
			m_scoreTexture = new texture("scoreBoard.png");
			m_Score.setTexture(m_scoreTexture);
			m_Score.setPosition(m_scorePosition);
			m_Score.setOrigin(vector(m_Score.getSize().x/2,
			m_Score.getSize().y/2));
			m_Score.setScale(1,1);

			m_Score.setLayer(295);

		// opacity

	m_pauseOpacityTexture.loadTexture("GameMenu/pauseScreenOpacity.png");
	m_pauseOpacitySprite.setTexture(&m_pauseOpacityTexture);
	m_pauseOpacitySprite.setLayer(297);

	m_tutorialNumber = 0;
			
}
void game::update(float deltaTime)
{
	m_flamingoHeadPressed = false;
	// gameStates
	if (!m_input->isButtonPressed(al::Button::MouseLeft))
	{
		ML_release = true;
	}

	switch(m_state)
	{

	case TitleScreen:
		// gui
		m_gui->update(deltaTime);

		m_gui->m_title = true;

		if (m_input->isButtonPressed(al::Button::MouseLeft))
		{
			m_state = Menu;
			/*m_state = ReturnTitle;*/
			/*m_state = Credits;*/
			m_gui->m_title =false;	
			ML_release = false;
		}
	
		break;
	
	case Play:
		
		// show text
		m_gui->m_Play = true;


		if(m_gui->m_button2->isPressed() && ML_release)
		{
			ML_release = false;
			m_state = Gamemenu;
		}
		else if(m_gui->m_button3->isPressed() && ML_release)
		{
			ML_release = false;

			if (!m_muted)
			{
				m_muted = true;
				m_soundLibrary->mute(true);
				m_gui->m_button3->setTexture(m_gui->m_buttonTextures[2]);
			}
			else
			{
				m_muted = false;
				m_soundLibrary->mute(false);
				m_gui->m_button3->setTexture(m_gui->m_buttonTextures[1]);
			}
		}
		else if(m_input->isButtonPressed(al::Button::MouseLeft) && ML_release)
		{
			ML_release = false;
			m_flamingoHeadPressed = true;
		}
			

		
		
		if(!m_input->isKeyPressed(al::Key::Menu))
			M_release = true;
		else if (M_release)
		{
			m_soundLibrary->m_musics[0]->pause();
			M_release = false;
			m_state = Gamemenu;
			
		}
		// hitbox

		//flamingo
		m_flamingo->update(deltaTime, m_flamingoHeadPressed);

		// nest
		m_nest->update(deltaTime);

		// enemy
		m_enemy->update(deltaTime);

		// pickups
		m_pickups->update(deltaTime);

		// backGround
		m_background->update(deltaTime);

		// gui
		m_gui->update(deltaTime);

		// titlecard
		m_titleCard->update(deltaTime);
		

		break;
	
	case Menu:

		m_gui->update(deltaTime);
		m_gui->m_menu = true;
		
		if(m_gui->m_mainbutton1->isPressed() && ML_release)
			{
				ML_release = false;
				m_state = Play;
				m_gui->m_menu = false;
			}
		if(m_gui->m_mainbutton2->isPressed() && ML_release)
			{
				ML_release = false;
				m_state = Tutorial;
				m_gui->m_menu = false;
			}
		if(m_gui->m_mainbutton3->isPressed() && ML_release)
			{
				ML_release = false;
				m_state = Credits;
				m_gui->m_menu = false;
			}
		if(m_gui->m_mainbutton4->isPressed() && ML_release)
			{
				m_ReturnCheck.setPosition(vector(640,620));
				ML_release = false;
				m_state = Quit;
				
			}

		//mainbutton4


		else if(m_input->isButtonPressed(al::Button::MouseLeft))
				{
				ML_release = false;
				}
	


		break;
	case Tutorial:
		m_gui->update(deltaTime);
		m_gui->m_tutorial = true;
		
		

		
		
		if(m_gui->m_tutorialbutton1->isPressed() && ML_release)
		{
			ML_release = false;
			m_tutorialNumber++;
				
			switch(m_tutorialNumber)
			{
			case 0:
				break;
			case 1:
				std::cout<<"Yksi"<<std::endl;
				break;
			case 2:
				std::cout<<"kaksi"<<std::endl;
				break;
			case 3:
				break;
			}
		}
		else if(m_input->isButtonPressed(al::Button::MouseLeft))
		{
			ML_release = false;
		}

		
		
		break;
	case Credits:
		m_gui->m_credits = true;
		m_gui->update(deltaTime);
		if(m_gui->m_xbutton->isPressed() && ML_release)
			{
				ML_release = false;
				m_state = Menu;
				m_gui->m_credits = false;
			}

		else if(m_input->isButtonPressed(al::Button::MouseLeft))
				{
				ML_release = false;
				}


		break;
	case Options:
		m_gui->m_Options = true;	
		m_gui->update(deltaTime);

			if(m_gui->m_donebutton->isPressed() && ML_release)
			{
				ML_release = false;
				m_state = Gamemenu;
				m_gui->m_Options = false;
			}
			else if(m_gui->m_plusmusic->isPressed() && ML_release)
				{
#if _DEBUG
					std::cout<<"plusmusic"<<std::endl;
#endif
					ML_release = false;
					m_soundLibrary->setMusicVolume(m_soundLibrary->m_musicVolume+10);
				}
			else if(m_gui->m_minusmusic->isPressed() && ML_release)
				{
#if _DEBUG
					std::cout<<"minusmusic"<<std::endl;
#endif
					ML_release = false;
					m_soundLibrary->setMusicVolume(m_soundLibrary->m_musicVolume-10);
				}
			else if(m_gui->m_plussounds->isPressed() && ML_release)
				{
#if _DEBUG
					std::cout<<"plussounds"<<std::endl;
#endif
					ML_release = false;
						m_soundLibrary->setSoundsVolume(m_soundLibrary->m_soundVolume+10);
				}
			else if(m_gui->m_minussounds->isPressed() && ML_release)
				{
#if _DEBUG
					std::cout<<"minussounds"<<std::endl;
#endif
					ML_release = false;
					m_soundLibrary->setSoundsVolume(m_soundLibrary->m_soundVolume-10);
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
				m_state = Play;
				m_gui->m_Gmenu = false;
			}
			else if(m_gui->m_Gmenubutton1->isPressed() && ML_release)
			{
				ML_release = false;
				m_state = Play;
				
				m_gui->m_Gmenu = false;
			}
			else if(m_gui->m_Gmenubutton2->isPressed() && ML_release)
			{
				ML_release = false;
				m_state = Play;
				reset();
				
				m_gui->m_Gmenu = false;
			}
			else if(m_gui->m_Gmenubutton3->isPressed() && ML_release)
			{
				ML_release = false;
				m_state = Options;
				m_gui->m_Gmenu = false;
			}
			else if(m_gui->m_Gmenubutton4->isPressed() && ML_release)
			{
				m_ReturnCheck.setPosition(vector(640,375));
				ML_release = false;
				m_state = ReturnTitle;
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
				m_state = Menu;
				
				m_gui->m_returnTitle = false;
				m_gui->m_Play = false;
			}
			else if(m_gui->m_nobutton->isPressed() && ML_release)
			{
				ML_release = false;
				m_state = Gamemenu;
				
				m_gui->m_returnTitle = false;
			}
			else if(m_input->isButtonPressed(al::Button::MouseLeft))
			{
				ML_release = false;
			}
		break;

		case Quit:
			m_gui->update(deltaTime);
			m_gui->m_quit = true;

			/*m_ReturnCheck.setPosition(vector(640,600));*/

			if(m_gui->m_yesbutton2->isPressed() && ML_release)
			{
				ML_release = false;
				m_gui->m_quit = false;
				m_viewport->close();
			}
			else if(m_gui->m_nobutton2->isPressed() && ML_release)
			{
				ML_release = false;
				m_state = Menu;
				
				m_gui->m_quit = false;
			}
			else if(m_input->isButtonPressed(al::Button::MouseLeft))
			{
				ML_release = false;
				
			}
		break;
	}
		
	




	// particles
	m_particleEngine->update(deltaTime);


}
void game::draw()
{
	// gameStates

		switch(m_state)
	{
	case TitleScreen:
		// titlecard
		m_titleCard->draw(m_viewport);
		m_viewport->draw(&m_logoSprite);
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

	case Tutorial:
		m_gui->draw(m_viewport);
	case Play:
		// backGround
		m_background->draw(m_viewport);

		m_viewport->draw(&m_Score);

		// nest
		m_nest->draw(m_viewport);

		// enemy
		m_enemy->draw(m_viewport);

		// pickups
		m_pickups->draw(m_viewport);

		// flamingo
		m_flamingo->draw(m_viewport);		

		if(m_gui->m_tutorial == true || m_gui->m_Gmenu == true || m_gui->m_returnTitle ==true)
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
		m_gui->draw(m_viewport);

		break;
	case Quit:
		m_viewport->draw(&m_ReturnCheck);
		m_gui->draw(m_viewport);
		m_titleCard->draw(m_viewport);
	}


	// animation


	// particles
	m_particleEngine->draw(m_viewport);

	
}

void game::reset()
{
	m_nest->reset();
	m_enemy->reset();
	m_pickups->reset();
	m_gui->reset();
}

#if _DEBUG
void game::drawDebugInfo(sf::RenderWindow *window)
{
	collide->DrawHitboxes(window);
	m_pickups->drawHitBoxes(window);
}
#endif

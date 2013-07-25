#include "game.h"
using namespace al;

game::game(sf::RenderWindow* Window, viewport* Viewport)
	:	window(Window),
		m_viewport(Viewport)
{
	////sound
	m_soundLibrary = new soundLibrary();
	m_soundLibrary->m_musics[0]->play();

	//// load Title Screen
	m_titleCard = new titleCard();
	m_titleCard->draw(Viewport);

	m_logoPosition = vector(640, 580);
	m_logoTexture = new texture("nameLogo.png");
	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setPosition(m_logoPosition);
	m_logoSprite.setOrigin(vector(m_logoSprite.getSize().x/2, m_logoSprite.getSize().y/2));
	m_logoSprite.setScale(1,1);
	Viewport->draw(&m_logoSprite);
}
game::~game()
{
#if _DEBUG
	std::cout<<"deleting maingame... "<<std::endl;
#endif
	delete m_font;
	delete m_font2;
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
	delete m_counterTexture;
	delete m_tutorial1Texture;
	delete m_tutorial2Texture;
	delete m_tutorial3Texture;
	delete m_tutorial4Texture;
	delete m_tutorial5Texture;
#if _DEBUG
	std::cout<<"done deleting maingame"<<std::endl;
#endif
}

void game::init()
{
	m_muted = false;
	m_input = new input(window);

	m_font = new font();
	m_font2 = new font();

	m_font->loadFromFile("arial.ttf");
	m_font2->loadFromFile("Arial black.ttf");

	DIFFICULTY = 1;
	
	// particles
	m_particleEngine = new particleEngine(m_font2);

	// gameStates

	m_state = TitleScreen;

	// gui
	m_gui = new gui(this);

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

			m_gameoverPosition = vector();
			m_gameoverTexture = new texture("gameoverScreen.png");
			m_gameoverSprite.setTexture(m_gameoverTexture);
			m_gameoverSprite.setPosition(m_gameoverPosition);
			m_gameoverSprite.setScale(1,1);
			m_gameoverSprite.setLayer(297);

			m_counterPosition = vector(0,650);
			m_counterTexture = new texture("eggCounter.png");
			m_counterSprite.setTexture(m_counterTexture);
			m_counterSprite.setPosition(m_counterPosition);
			m_counterSprite.setScale(0.3333f,0.3333f);
			m_counterSprite.setLayer(296);

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

			m_scorePosition = (vector(130,70));
			m_scoreTexture = new texture("scoreBoard.png");
			m_Score.setTexture(m_scoreTexture);
			m_Score.setPosition(m_scorePosition);
			m_Score.setOrigin(vector(m_Score.getSize().x/2,
			m_Score.getSize().y/2));
			m_Score.setScale(1,1);

			m_Score.setLayer(295);

			m_tutorial1Position = (vector(640,360));
			m_tutorial1Texture = new texture("Tutorials/tuto1.png");
			m_tutorial1.setTexture(m_tutorial1Texture);
			m_tutorial1.setPosition(m_tutorial1Position);
			m_tutorial1.setOrigin(vector(m_tutorial1.getSize().x/2,
			m_tutorial1.getSize().y/2));
			m_tutorial1.setScale(1,1);

			m_tutorial1.setLayer(295);

			m_tutorial2Position = (vector(640,360));
			m_tutorial2Texture = new texture("Tutorials/tuto2.png");
			m_tutorial2.setTexture(m_tutorial2Texture);
			m_tutorial2.setPosition(m_tutorial2Position);
			m_tutorial2.setOrigin(vector(m_tutorial2.getSize().x/2,
			m_tutorial2.getSize().y/2));
			m_tutorial2.setScale(1,1);

			m_tutorial2.setLayer(295);

			m_tutorial3Position = (vector(640,360));
			m_tutorial3Texture = new texture("Tutorials/tuto3.png");
			m_tutorial3.setTexture(m_tutorial3Texture);
			m_tutorial3.setPosition(m_tutorial3Position);
			m_tutorial3.setOrigin(vector(m_tutorial3.getSize().x/2,
			m_tutorial3.getSize().y/2));
			m_tutorial3.setScale(1,1);

			m_tutorial3.setLayer(295);

			m_tutorial4Position = (vector(640,360));
			m_tutorial4Texture = new texture("Tutorials/tuto4.png");
			m_tutorial4.setTexture(m_tutorial4Texture);
			m_tutorial4.setPosition(m_tutorial4Position);
			m_tutorial4.setOrigin(vector(m_tutorial4.getSize().x/2,
			m_tutorial4.getSize().y/2));
			m_tutorial4.setScale(1,1);

			m_tutorial4.setLayer(295);

			m_tutorial5Position = (vector(640,360));
			m_tutorial5Texture = new texture("Tutorials/tuto5.png");
			m_tutorial5.setTexture(m_tutorial5Texture);
			m_tutorial5.setPosition(m_tutorial5Position);
			m_tutorial5.setOrigin(vector(m_tutorial5.getSize().x/2,
			m_tutorial5.getSize().y/2));
			m_tutorial5.setScale(1,1);
					  
			m_tutorial5.setLayer(295);

		// opacity

	m_pauseOpacityTexture.loadTexture("GameMenu/pauseScreenOpacity.png");
	m_pauseOpacitySprite.setTexture(&m_pauseOpacityTexture);
	m_pauseOpacitySprite.setLayer(297);

	m_tutorialNumber = 1;

	m_countSpeed = 0;
	m_countingEggs = false;

	m_input->setMousePosition(vector());
}
void game::update(float deltaTime)
{
	if (deltaTime > 0.1f)
		deltaTime = 0.1f;

	m_flamingoHeadPressed = false;

	if (m_input->getMousePosition() == vector())
	{
		ML_release = true;
	}
	// gameStates


	switch(m_state)
	{

	case TitleScreen:
		// gui
		m_gui->update(deltaTime);

		m_gui->m_title = true;

		if (m_input->getMousePosition() != vector())
		{
			m_state = Menu;
			m_gui->m_title =false;	
			ML_release = false;
		}
	
		break;
	
	case Play:

		if (m_gui->m_errorCount >= 3)
		{
			m_state = GameOver;// game over
			m_gui->m_gameOver = true;
			m_timer = 0;
			m_gui->TITLEtext->setString("Click or tap to return to Main Menu");
			//m_gui->TITLEtext->setLayer(300);
			//m_gui->TITLEtext->setColor(255,255,0,255);
		}

		if (m_nest->m_eggCount == 0)
		{
			m_enemy->m_nestHasEggs = false;
		}

		if (m_nest->m_hatchCount + m_nest->m_eggCount == 0)
		{

			m_yearCount++;
			m_difficultyMultiplier++;
			m_gui->m_yearPos.x = -500;

			m_state = Levelscore;
			m_countSpeed = m_nest->m_flamCount+10;
			//m_countingEggs = true;
			//m_nest->m_countingEggs = true;
			m_enemy->reset();
			m_enemy->m_enemySpeed = m_difficultyMultiplier;
			
			break;
		}
		// show text
		m_gui->m_Play = true;
		//m_gui->update(deltaTime);


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
		else if(m_input->isButtonPressed(MouseLeft) && ML_release)
		{
			ML_release = false;
			m_flamingoHeadPressed = true;
		}
			


		//flamingo
		m_flamingo->update(deltaTime, m_flamingoHeadPressed);

		// enemy
		m_enemy->update(deltaTime);

		if (m_enemy->m_takingEgg)
		{
			if (!m_nest->enemyTakingEgg())
			{
				m_enemy->m_tookEgg = false;
				
			}
			else
			{
				m_nest->shocked();
				m_gui->addScore(m_nest->m_eggPosition,-500,true);
			}
			m_enemy->m_takingEgg = false;
		}

		// nest
		m_nest->update(deltaTime);

		// pickups
		m_pickups->update(deltaTime);

		// backGround
		m_background->update(deltaTime);

		// gui
		m_gui->update(deltaTime);

		// titlecard
		

		break;

	case Levelscore:

		m_gui->update(deltaTime);
		m_nest->update(deltaTime);
		m_gui->m_levelscore = true;

		if (m_input->getMousePosition() != vector())
		{
			ML_release = false;

			for (int i = 0; i < 6; ++i)
				m_nest->addEgg();
			m_state = Play;
			m_gui->m_levelscore = false;
			m_nest->update(deltaTime);
		}

		break;

	case GameOver:
		
		m_gui->update(deltaTime);
		m_timer += deltaTime;

		if(m_timer > 3)
		{
			m_gui->m_title = true;
			
			if (m_input->getMousePosition() != vector())
			{
				ML_release = false;
				m_state = Menu;
				/*m_state = ReturnTitle;*/
				/*m_state = Credits;*/
				m_gui->m_title =false;	
				m_timer = 0;
				reset();
				
				m_gui->m_returnTitle = false;
				m_gui->m_Play = false;
				m_gui->m_gameOver = false;
			}
		}

		break;
	
	case Menu:
		m_tutorialNumber= 1;
		m_gui->update(deltaTime);
		m_gui->m_menu = true;
		
		if(m_gui->m_mainbutton1->isPressed() && ML_release)
		{
			ML_release = false;
			m_state = Play;
			m_gui->m_menu = false;
			reset();
		}
		else if(m_gui->m_mainbutton2->isPressed() && ML_release)
		{
			ML_release = false;
			m_state = Tutorial;
			m_gui->m_menu = false;
		}
		else if(m_gui->m_mainbutton3->isPressed() && ML_release)
		{
			ML_release = false;
			m_state = Credits;
			m_gui->m_menu = false;
		}
		else if(m_gui->m_mainbutton4->isPressed() && ML_release)
		{
			m_ReturnCheck.setPosition(vector(640,620));
			ML_release = false;
			m_state = Quit;
		}
		else if(m_input->isButtonPressed(MouseLeft))
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
		}
		else if(m_gui->m_tutorialbutton2->isPressed() && ML_release)
		{
			ML_release = false;
			m_tutorialNumber--;
		}
		else if(m_input->isButtonPressed(MouseLeft))
		{
			ML_release = false;
		}

		switch(m_tutorialNumber)
		{
		case 0:
			m_state = Menu;
			m_gui->m_tutorial = false;
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			m_state = Menu;
			m_gui->m_tutorial = false;

			break;
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
		else if(m_input->isButtonPressed(MouseLeft))
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
				ML_release = false;
#if _DEBUG
				std::cout<<"plusmusic"<<std::endl;
#endif
				m_soundLibrary->setMusicVolume(m_soundLibrary->m_musicVolume+10);
			}
			else if(m_gui->m_minusmusic->isPressed() && ML_release)
			{
				ML_release = false;
#if _DEBUG
				std::cout<<"minusmusic"<<std::endl;
#endif
				m_soundLibrary->setMusicVolume(m_soundLibrary->m_musicVolume-10);
			}
			else if(m_gui->m_plussounds->isPressed() && ML_release)
			{
				ML_release = false;
#if _DEBUG
				std::cout<<"plussounds"<<std::endl;
#endif
				m_soundLibrary->setSoundsVolume(m_soundLibrary->m_soundVolume+10);
			}
			else if(m_gui->m_minussounds->isPressed() && ML_release)
			{
				ML_release = false;
#if _DEBUG
				std::cout<<"minussounds"<<std::endl;
#endif
				m_soundLibrary->setSoundsVolume(m_soundLibrary->m_soundVolume-10);
			}
			else if(m_input->isButtonPressed(MouseLeft))
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
				ML_release = false;
				m_ReturnCheck.setPosition(vector(640,375));
				m_state = ReturnTitle;
				m_gui->m_Gmenu = false;
			}
			else if(m_input->isButtonPressed(MouseLeft))
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
				reset();
				
				m_gui->m_returnTitle = false;
				m_gui->m_Play = false;
			}
			else if(m_gui->m_nobutton->isPressed() && ML_release)
			{
				ML_release = false;
				m_state = Gamemenu;
				
				m_gui->m_returnTitle = false;
			}
			else if(m_input->isButtonPressed(MouseLeft))
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
			else if(m_input->isButtonPressed(MouseLeft))
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
	
	case Tutorial:
		m_gui->draw(m_viewport);
		
		switch(m_tutorialNumber)
				{
				case 0:
					break;
				case 1:
					m_viewport->draw(&m_tutorial1);
					break;
				case 2:
					m_viewport->draw(&m_tutorial2);
					break;
				case 3:
					m_viewport->draw(&m_tutorial3);
					break;
				case 4:
					m_viewport->draw(&m_tutorial4);
					break;
				case 5:
					m_viewport->draw(&m_tutorial5);
					break;
					}
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
	case Levelscore:
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

		if(m_gui->m_tutorial == true || m_gui->m_Gmenu == true || m_gui->m_returnTitle ==true ||m_gui->m_Options ==true)
		{
			// pauseopacity
			m_viewport->draw(&m_pauseOpacitySprite);
		}

		// gui
		m_gui->draw(m_viewport);


		// counter
		m_viewport->draw(&m_counterSprite);


		break;

	case GameOver:

		m_viewport->draw(&m_gameoverSprite);
		m_gui->draw(m_viewport);

		//m_viewport->draw(m_gui->TITLEtext);

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

	if (!m_input->isButtonPressed(MouseLeft))
		m_input->setMousePosition(vector());
}

void game::reset()
{
	m_nest->reset();
	m_enemy->reset();
	m_pickups->reset();
	m_gui->reset();
	m_flamingo->reset();
	m_timer = 0;
	m_countingEggs = false;
	m_yearCount = 0;
	m_difficultyMultiplier = 0;
}

#if _DEBUG
void game::drawDebugInfo(sf::RenderWindow *window)
{
	collide->DrawHitboxes(window);
	m_pickups->drawHitBoxes(window);
}
#endif

#include "gui.h"

using namespace al;

button::button(al::texture* Texture, al::vector Position, al::input* Input,soundLibrary* SoundLibrary)
{
	m_input = Input;
	m_position = Position;
	setTexture(Texture);
	m_soundLibrary = SoundLibrary;
}
button::~button()
{
	delete m_animation;
}

void button::setTexture(al::texture* Texture)
{
	//m_texture.loadTexture(TextureName);
	m_sprite.setTexture(Texture);
	m_animation = new animation(&m_sprite, 1, int(m_sprite.getTextureSize().x/2), int(m_sprite.getTextureSize().y/2), false, 0);
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(vector(m_sprite.getSize().x/2, m_sprite.getSize().y/2));
	m_sprite.setScale(1,1);
	/*m_sprite.setLayer(296);*/
}
void button::update(float DeltaTime)
{
	m_animation->update(DeltaTime);
}
void button::draw(al::viewport* Viewport)
{
	Viewport->draw(&m_sprite);
}
bool button::isPressed()
{
	if(mouseOver())
	{
		return true;
		if(m_input->isButtonPressed(MouseLeft))
		{
			if (m_animation->getCurrentFrame() == 1)
			{
				m_animation->ChangeAnimation(2,0,2,100);
				m_soundLibrary->m_sounds[4]->play();
			}
			return true;
		}
		else
		{
			m_animation->ChangeAnimation(1,0,1,100);
		}
	}
	else
		m_animation->ChangeAnimation(0,0,0,100);

	return false;
}

bool button::mouseOver()
{
	if (rectangle(m_position - m_sprite.getSize()/2,m_sprite.getSize()).contains(m_input->getMousePosition()))
		return true;
	return false;
}

//////////////////////////////////////////////////////////////////////////

titleCard::titleCard()
{
	m_titlePosition = vector(640, 360);
	setTexture("titlescreen.png");

	
	
} 
titleCard::~titleCard()
{

}

void titleCard::setTexture(std::string TextureName)
{
	m_texture.loadTexture(TextureName);
	m_titleSprite.setTexture(&m_texture);
	//m_titleAnimation = new animation(&m_titleSprite, 1, m_titleSprite.getTextureSize().x/2, m_titleSprite.getTextureSize().y/2, false, 0);
	m_titleSprite.setPosition(m_titlePosition);
	m_titleSprite.setOrigin(vector(m_titleSprite.getSize().x/2, m_titleSprite.getSize().y/2));
	m_titleSprite.setScale(1,1);

}
void titleCard::draw(al::viewport* Viewport)
{
	Viewport->draw(&m_titleSprite);
	
}

//////////////////////////////////////////////////////////////////////////

gui::gui(game* Game)
{
	m_game = Game;
	m_input = Game->m_input;
	m_soundLibrary = Game->m_soundLibrary;
	m_particleEngine = Game->m_particleEngine;

	m_font = Game->m_font;// new font();
	m_font2 = Game->m_font2;// new font();

	// HP-basics
	HPmax = 100; //max HP
	HPtaken = 0; // damage/heal
	HPnow = HPmax-HPtaken;
	m_eggCount = 0;
	m_flamCount = 0;


	/*button = "test" button
	button2 = Listbutton
	button3 = mute-button*/

	//gameplay-buttons

	m_buttonTextures.push_back(new texture("buttons/menubutton.png")); // 0
	m_button2 = new button(m_buttonTextures.back(),vector(1200,75),m_input,m_soundLibrary);
	m_button2->m_sprite.setLayer(296);
	
	m_buttonTextures.push_back(new texture("buttons/muteButton1.png")); // 1
	m_button3 = new button(m_buttonTextures.back(),vector(1070,75),m_input, m_soundLibrary);
	m_button3->m_sprite.setLayer(296);
	m_buttonTextures.push_back(new texture("buttons/muteButton2.png")); // 2

	// GameMenu's buttons
	m_buttonTextures.push_back(new texture("GameMenu/MenuButton.png")); // 3
	m_Gmenubutton1 = new button(m_buttonTextures.back(),vector(628,331),m_input, m_soundLibrary);
	m_Gmenubutton1->m_sprite.setLayer(299);
	
	
	m_Gmenubutton2 = new button(m_buttonTextures.back(),vector(628,361),m_input, m_soundLibrary);
	m_Gmenubutton2->m_sprite.setLayer(299);
	
	
	m_Gmenubutton3 = new button(m_buttonTextures.back(),vector(628,391),m_input, m_soundLibrary);
	m_Gmenubutton3->m_sprite.setLayer(299);
	
	
	m_Gmenubutton4 = new button(m_buttonTextures.back(),vector(628,421),m_input, m_soundLibrary);
	m_Gmenubutton4->m_sprite.setLayer(299);
	
	// ReturnTitle buttons
	
	m_buttonTextures.push_back(new texture("GameMenu/yesButton.png")); // 4
	m_yesbutton = new button(m_buttonTextures.back(),vector(580,375),m_input, m_soundLibrary);
	m_yesbutton->m_sprite.setLayer(300);

	m_yesbutton2 = new button(m_buttonTextures.back(),vector(580,620),m_input, m_soundLibrary);
	m_yesbutton2->m_sprite.setLayer(300);
	
	m_buttonTextures.push_back(new texture("GameMenu/noButton.png")); // 5
	m_nobutton = new button(m_buttonTextures.back(),vector(687,375),m_input, m_soundLibrary);
	m_nobutton->m_sprite.setLayer(300);

	m_nobutton2 = new button(m_buttonTextures.back(),vector(687,620),m_input, m_soundLibrary);
	m_nobutton2->m_sprite.setLayer(300);
	
	m_buttonTextures.push_back(new texture("OptionsMenu/Done.png")); // 6
	m_donebutton = new button(m_buttonTextures.back(),vector(620,440),m_input, m_soundLibrary);
	m_donebutton->m_sprite.setLayer(300);
	
	m_buttonTextures.push_back(new texture("OptionsMenu/plus.png")); // 7
	m_plusmusic = new button(m_buttonTextures.back(),vector(748,323),m_input, m_soundLibrary);
	m_plusmusic->m_sprite.setLayer(300);
	
	m_plussounds = new button(m_buttonTextures.back(),vector(748,378),m_input, m_soundLibrary);
	m_plussounds->m_sprite.setLayer(300);

	m_buttonTextures.push_back(new texture("OptionsMenu/minus.png")); // 8
	m_minusmusic = new button(m_buttonTextures.back(),vector(667,323),m_input, m_soundLibrary);
	m_minusmusic->m_sprite.setLayer(300);
	
	m_minussounds = new button(m_buttonTextures.back(),vector(667,378),m_input, m_soundLibrary);
	m_minussounds->m_sprite.setLayer(300);

	// MainMenu buttons
	m_buttonTextures.push_back(new texture("MainMenu/playButton.png")); // 9
	m_mainbutton1 = new button(m_buttonTextures.back(),vector(628,490),m_input, m_soundLibrary);
	m_mainbutton1->m_sprite.setLayer(1);

	m_buttonTextures.push_back(new texture("MainMenu/instructionsButton.png")); // 10
	m_mainbutton2 = new button(m_buttonTextures.back(),vector(650,550),m_input, m_soundLibrary);
	m_mainbutton2->m_sprite.setLayer(1);
	
	m_buttonTextures.push_back(new texture("MainMenu/creditsButton.png")); // 11
	m_mainbutton3 = new button(m_buttonTextures.back(),vector(625,605),m_input, m_soundLibrary);
	m_mainbutton3->m_sprite.setLayer(1);
	
	m_buttonTextures.push_back(new texture("MainMenu/quitButton.png")); // 12
	m_mainbutton4 = new button(m_buttonTextures.back(),vector(626,670),m_input, m_soundLibrary);
	m_mainbutton4->m_sprite.setLayer(1);

	m_buttonTextures.push_back(new texture("Buttons/exitButton.png")); // 13
	m_xbutton = new button(m_buttonTextures.back(),vector(100,600),m_input, m_soundLibrary);
	m_xbutton->m_sprite.setLayer(300);

	m_buttonTextures.push_back(new texture("tutorialButton.png")); // 13
	m_tutorialbutton1 = new button(m_buttonTextures.back(),vector(1225,70),m_input, m_soundLibrary);
	m_tutorialbutton1->m_sprite.setLayer(300);
	
	
	m_tutorialbutton2 = new button(m_buttonTextures.back(),vector(50,70),m_input, m_soundLibrary);
	m_tutorialbutton2->m_sprite.setLayer(300);
	m_tutorialbutton2->m_sprite.setScale(-1,1);
	
	

	//m_font->loadFromFile("arial.ttf");
	//m_font2->loadFromFile("Arial black.ttf");

	
	
	HPtext = new text("HP-mittari", m_font, 50);
	TITLEtext = new text("Click or Tap the screen",m_font, 50);
	SCOREtext = new text("SCORE", m_font2,50);
	MUSICtext = new text("music volume", m_font2,20);
	SOUNDtext = new text("sounds volume", m_font2,20);
	EGGtext = new text("egg count", m_font2,40);
	FLAMtext = new text("flamingo count", m_font2,40);
	YEARtext = new text("year one", m_font2, 120);
	GSCOREtext = new text("Your score was: ",m_font2,23);
	GYEARtext = new text("bjsfgfhj", m_font2, 23);

	
	//// Layers, 296 and below will get dark, when paused. 298 will be bright when paused. ///

	HPtext->setColor();
	HPtext->setLayer(296);
	
	SCOREtext->setPosition(vector(60, 60));
	SCOREtext->setColor(83,77,67,255);
	SCOREtext->setLayer(298);
	
	TITLEtext->setPosition(vector(640,690));
	//TITLEtext->setColor();
	TITLEtext->setOriginPoint(5);
	TITLEtext->setLayer(300);

	MUSICtext->setPosition (vector(686,310));
	MUSICtext->setColor(83,77,67,255);
	MUSICtext->setLayer(299);

	SOUNDtext->setPosition (vector(686,365));
	SOUNDtext->setColor(83,77,67,255);
	SOUNDtext->setLayer(299);

	EGGtext->setPosition(vector(60,655));
	EGGtext->setColor(83,77,67,255);
	EGGtext->setLayer(299);
	
	FLAMtext->setPosition(vector(160,655));
	FLAMtext->setCharacterSize(23);
	FLAMtext->setColor(83,77,67,255);
	FLAMtext->setLayer(299);

	YEARtext->setCharacterSize(100);
	YEARtext->setColor();
	YEARtext->setOriginPoint(5);
	YEARtext->setLayer(299);

	GSCOREtext->setCharacterSize(25);
	GSCOREtext->setColor(83,77,67,255);
	GSCOREtext->setLayer(299);

	GYEARtext->setCharacterSize(25);
	GYEARtext->setColor(83,77,67,255);
	GYEARtext->setLayer(299);


	m_yearTexture = new texture("yearCompletedSign.png");
	m_yearSprite.setTexture(m_yearTexture);
	m_yearSprite.setOriginPoint(5);
	m_yearSprite.setPosition(vector(-200,-200));
	m_yearSprite.setLayer(299);

	m_goverTexture = new texture("gameOverScoreboard.png");
	m_goverSprite.setTexture(m_goverTexture);
	m_goverSprite.setOriginPoint(5);
	m_goverSprite.setPosition(vector(640, 360));
	m_goverSprite.setLayer(298);

	m_errorPosition = vector(100,650);
	m_errorTexture = new texture("flamingoHeadMistake.png");

	for(int i = 0; i < 3; i++)
	{
		m_errorSprites.push_back(new sprite(m_errorTexture));
		m_errorSprites[i]->setPosition(vector(m_errorPosition.x + i*80, m_errorPosition.y));
		m_errorSprites[i]->setLayer(296);
	}


	reset();
	m_Play = false;
}
gui::~gui()
{
#if _DEBUG
	std::cout<<"deleted gui"<<std::endl;
#endif
	delete HPtext;
	delete TITLEtext;
	delete SCOREtext;
	delete YEARtext;
	delete EGGtext;
	delete FLAMtext;
	delete m_button2;
	delete m_button3;
	delete m_Gmenubutton1;
	delete m_Gmenubutton2;
	delete m_Gmenubutton3;
	delete m_Gmenubutton4;
	delete m_yesbutton;
	delete m_nobutton;
	delete m_yesbutton2;
	delete m_nobutton2;
	delete m_donebutton;
	delete m_plusmusic;
	delete m_plussounds;
	delete m_minusmusic;
	delete m_minussounds;
	delete MUSICtext;
	delete SOUNDtext;
	delete m_mainbutton1;
	delete m_mainbutton2;
	delete m_mainbutton3;
	delete m_mainbutton4;
	delete m_xbutton;
	delete m_tutorialbutton1;
	delete m_errorTexture;

	for (unsigned int i = 0; i < m_errorSprites.size(); ++i)
	{
		delete m_errorSprites[i];
	}
	
	for (unsigned int i = 0; i < m_buttonTextures.size(); ++i)
	{
		delete m_buttonTextures[i];
	}
}

void gui::update(float DeltaTime)
{
	switch (m_game->m_state)
	{
	case TitleScreen:
		break;
	case Play:
		break;
	case Levelscore:
		break;
	case GameOver:
		break;
	case Menu:
		break;
	case Tutorial:
		break;
	case Credits:
		break;
	case Options:
		break;
	case Gamemenu:
		break;
	case ReturnTitle:
		break;
	case Quit:
		break;
	}
	
	//edit  HP settings
	if( HPnow < 0) 
	{
		HPnow = 0;
	}

	if (m_Play)
	{
		HPtext->setString("HP: Hitpoints " + std::to_string((long double)HPnow) + " / " + std::to_string((long double)HPmax));
		SCOREtext->setString(std::to_string(long double(floor(SCORE+0.5f))));
		EGGtext->setString(std::to_string((long double)m_eggCount));
		FLAMtext->setString(std::to_string((long double)m_flamCount));
		m_button2->update(DeltaTime);
		m_button3->update(DeltaTime);
		//HPtext->


	}
	else
		HPtext->setString("");	

	if (m_Options)
	{
		m_donebutton->update(DeltaTime);
		m_plusmusic->update(DeltaTime);
		m_plussounds->update(DeltaTime);
		m_minusmusic->update(DeltaTime);
		m_minussounds->update(DeltaTime);
		MUSICtext->setString(std::to_string((long double)m_soundLibrary->m_musicVolume ));
		SOUNDtext->setString(std::to_string((long double)m_soundLibrary->m_soundVolume));
		

	}

	if (m_tutorial)
	{
		m_tutorialbutton1->update(DeltaTime);
		m_tutorialbutton2->update(DeltaTime);
	}

	if (m_returnTitle)
	{
		m_yesbutton->update(DeltaTime);
		m_nobutton->update(DeltaTime);

	}	
	if (m_quit)
	{
		m_yesbutton2->update(DeltaTime);
		m_nobutton2->update(DeltaTime);
	}
	if (m_menu)
	{
		m_mainbutton1->update(DeltaTime);
		m_mainbutton2->update(DeltaTime);
		m_mainbutton3->update(DeltaTime);
		m_mainbutton4->update(DeltaTime);
	}

	if (m_Play)
	{
		m_button2->update(DeltaTime);
		m_button3->update(DeltaTime);
	}
	
	if (m_Gmenu)
	{
		m_Gmenubutton1->update(DeltaTime);
		m_Gmenubutton2->update(DeltaTime);
		m_Gmenubutton3->update(DeltaTime);
		m_Gmenubutton4->update(DeltaTime);
	}
	if (m_credits)
	{
		m_xbutton->update(DeltaTime);
	}
	if (m_levelscore)
	{	
		if(m_yearPos.x >= 650)
		{
			m_yearPos.x = 650;
		}
		else
		{
			m_yearPos.x += DeltaTime*500;
			m_yearSprite.setPosition(m_yearPos);
		}
	}
	else
	{	
		if(m_yearPos.x >= 1600)
		{
			m_yearPos.x = 1600;
		}
		else
		{
			m_yearPos.x += DeltaTime*500;
			m_yearSprite.setPosition(m_yearPos);
		}
	}
	if (m_gameOver)
	{

	}
}
void gui::draw(al::viewport* Viewport)
{
	switch (m_game->m_state)
	{
	case TitleScreen:
		Viewport->draw(TITLEtext);
		break;
	case Play:
		m_button2->draw(Viewport); //button2
		m_button3->draw(Viewport); //button3
		//Viewport->draw(HPtext);
		Viewport->draw(SCOREtext);
		Viewport->draw(EGGtext);
		//Viewport->draw(FLAMtext);

		for(unsigned int i = 0; i < m_errorSprites.size(); ++i)
		{
			Viewport->draw(m_errorSprites[i]);
		}
		Viewport->draw(&m_yearSprite);
		break;
	case Levelscore:
		Viewport->draw(&m_yearSprite);
		break;
	case GameOver:
		if(m_game->m_timer > 3)
		{
			Viewport->draw(TITLEtext);
		}
		Viewport->draw(&m_goverSprite);

		FLAMtext->setPosition(vector(500,400));
		FLAMtext->setString(std::string("Adult flamingoes:  ")
								+ std::to_string((long double)m_flamCount));
		Viewport->draw(FLAMtext);

		GSCOREtext->setPosition(vector(500, 350));
		GSCOREtext->setString(std::string("Score:  ")
								+ std::to_string((long double)SCORE));
		Viewport->draw(GSCOREtext);

		GYEARtext->setPosition(vector(500, 450));
		GYEARtext->setString(std::string("Years passed:  ")
								+ std::to_string((long double)m_game->m_yearCount));
		Viewport->draw(GYEARtext);


		break;
	case Menu:
		m_mainbutton1->draw(Viewport);
		m_mainbutton2->draw(Viewport);
		m_mainbutton3->draw(Viewport);
		m_mainbutton4->draw(Viewport);
		break;
	case Tutorial:
		m_tutorialbutton1->draw(Viewport);
		m_tutorialbutton2->draw(Viewport);
		break;
	case Credits:
		m_xbutton->draw(Viewport);
		break;
	case Options:
		m_donebutton->draw(Viewport);
		m_donebutton->draw(Viewport);
		m_plusmusic->draw(Viewport);
		m_plussounds->draw(Viewport);
		m_minusmusic->draw(Viewport);
		m_minussounds->draw(Viewport);
		Viewport->draw(MUSICtext);
		Viewport->draw(SOUNDtext);
		break;
	case Gamemenu:
		m_Gmenubutton1->draw(Viewport);
		m_Gmenubutton2->draw(Viewport);
		m_Gmenubutton3->draw(Viewport);
		m_Gmenubutton4->draw(Viewport);
		m_button2->draw(Viewport); //button2
		m_button3->draw(Viewport); //button3
		//Viewport->draw(HPtext);
		Viewport->draw(SCOREtext);
		Viewport->draw(EGGtext);
		Viewport->draw(GYEARtext);
		//Viewport->draw(FLAMtext);

		for(unsigned int i = 0; i < m_errorSprites.size(); ++i)
		{
			Viewport->draw(m_errorSprites[i]);
		}
		break;
	case ReturnTitle:
		m_yesbutton->draw(Viewport);
		m_nobutton->draw(Viewport);
		break;
	case Quit:
		m_yesbutton2->draw(Viewport);
		m_nobutton2->draw(Viewport);
		break;
	}

}
void gui::addScore(vector Position,float Score, bool Fatal)
{
	Score *= 1+(m_game->m_difficultyMultiplier/10.0f);
	SCORE += Score;
	m_particleEngine->addScore(Position,Score);
	if (SCORE < 0)
		SCORE = 0;

	if(Score < 0 && Fatal)
	{
		m_errorCount++;

		if (m_errorCount < 0)
				m_errorCount = 0;

		if (m_errorCount > 3)
				m_errorCount = 3;

		updateErrorlist();
	}

}
void gui::updateErrorlist()
{
		switch(m_errorCount)
		{
		case 0:
			m_errorSprites[0]->setColor(255,255,255,255);
			m_errorSprites[1]->setColor(255,255,255,255);
			m_errorSprites[2]->setColor(255,255,255,255);
			
			break;

		case 1:
			m_errorSprites[0]->setColor(30,30,30,255);
			m_errorSprites[1]->setColor(255,255,255,255);
			m_errorSprites[2]->setColor(255,255,255,255);
			
			break;

		case 2:
			m_errorSprites[0]->setColor(30,30,30,255);
			m_errorSprites[1]->setColor(30,30,30,255);
			m_errorSprites[2]->setColor(255,255,255,255);
			
			break;

		case 3:
			m_errorSprites[0]->setColor(30,30,30,255);
			m_errorSprites[1]->setColor(30,30,30,255);
			m_errorSprites[2]->setColor(30,30,30,255);

			break;
		}
}
void gui::reset()
{
	
	m_title = false;
	m_Play = true;
	m_menu = false;
	m_Gmenu = false;
	m_Options = false;
	m_returnTitle = false;
	m_credits= false;
	m_quit = false;
	m_tutorial = false;
	m_levelscore = false;
	m_gameOver = false;
	m_errorCount = 0;
	updateErrorlist();

	m_yearPos = vector(1600,250);
	YEARtext->setPosition(m_yearPos);


	SCORE= 0;
}


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
	float asdf = m_sprite.getTextureSize().x/2;
	m_animation = new animation(&m_sprite, 1, m_sprite.getTextureSize().x/2, m_sprite.getTextureSize().y/2, false, 0);
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
		if(m_input->isButtonPressed(al::Button::MouseLeft))
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
	setTexture("titlescreen_Placeholder.png");
	
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
void titleCard::update(float DeltaTime)
{

}
void titleCard::draw(al::viewport* Viewport)
{
	Viewport->draw(&m_titleSprite);
}



//////////////////////////////////////////////////////////////////////////

gui::gui(al::input* Input, soundLibrary* SoundLibrary)
{
	m_soundLibrary = SoundLibrary;
	m_input = Input;
	m_pause = false;
	m_title = false;
	m_Play = false;
	m_menu = false;
	m_Gmenu = false;
	m_Options = false;
	m_returnTitle = false;
	m_credits= false;
	m_soundLibrary = SoundLibrary;

	
	// HP-basics
	HPmax = 100; //max HP
	HPtaken = 0; // damage/heal
	HPnow = HPmax-HPtaken;


	SCORE= 0;
	
	
	

	



	/*button = "test" button
	button2 = Listbutton
	button3 = mute-button*/

	//gameplay-buttons

	m_buttonTextures.push_back(new texture("buttons/menubutton.png")); // 0
	m_button2 = new button(m_buttonTextures.back(),vector(1054,75),m_input,m_soundLibrary);
	m_button2->m_sprite.setLayer(296);
	
	m_buttonTextures.push_back(new texture("buttons/muteButton1.png")); // 1
	m_button3 = new button(m_buttonTextures.back(),vector(908,75),m_input, m_soundLibrary);
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
	
	m_buttonTextures.push_back(new texture("GameMenu/noButton.png")); // 5
	m_nobutton = new button(m_buttonTextures.back(),vector(687,375),m_input, m_soundLibrary);
	m_nobutton->m_sprite.setLayer(300);
	
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
	m_mainbutton2 = new button(m_buttonTextures.back(),vector(667,550),m_input, m_soundLibrary);
	m_mainbutton2->m_sprite.setLayer(1);
	
	m_buttonTextures.push_back(new texture("MainMenu/creditsButton.png")); // 11
	m_mainbutton3 = new button(m_buttonTextures.back(),vector(630,600),m_input, m_soundLibrary);
	m_mainbutton3->m_sprite.setLayer(1);
	
	m_buttonTextures.push_back(new texture("MainMenu/quitButton.png")); // 12
	m_mainbutton4 = new button(m_buttonTextures.back(),vector(626,666),m_input, m_soundLibrary);
	m_mainbutton4->m_sprite.setLayer(1);

	m_buttonTextures.push_back(new texture("Buttons/exitButton.png")); // 13
	m_xbutton = new button(m_buttonTextures.back(),vector(100,600),m_input, m_soundLibrary);
	m_xbutton->m_sprite.setLayer(300);

	
	
	m_font = new font();
	m_font2 = new font();

	m_font->loadFromFile("arial.ttf");
	m_font2->loadFromFile("Arial black.ttf");

	
	
	HPtext = new text("HP-mittari", m_font, 50);
	PAUSEtext = new text(".::pAuSE::.", m_font, 50);
	TITLEtext = new text("Press SPACE",m_font, 50);
	SCOREtext = new text("SCORE", m_font,50);
	MUSICtext = new text("music volume", m_font2,20);
	SOUNDtext = new text("sounds volume", m_font2,20);

	
	//// Layers, 296 and below will get dark, when paused. 298 will be bright when paused. ///

	HPtext->setColor();
	HPtext->setLayer(296);
	
	SCOREtext->setPosition(vector(0, 50));
	SCOREtext->setColor();
	SCOREtext->setLayer(296);

	PAUSEtext->setPosition(vector(640, 360));
	PAUSEtext->setOrigin(vector(PAUSEtext->getGlobalBounds().width/2,PAUSEtext->getGlobalBounds().height/2));
	PAUSEtext->setColor();
	PAUSEtext->setLayer(298);

	TITLEtext->setPosition(vector(500,550));
	TITLEtext->setColor();
	TITLEtext->setLayer(298);

	MUSICtext->setPosition (vector(686,310));
	MUSICtext->setColor(83,77,67,255);
	MUSICtext->setLayer(299);

	SOUNDtext->setPosition (vector(686,365));
	SOUNDtext->setColor(83,77,67,255);
	SOUNDtext->setLayer(299);
	//std::cout << text.getPosition().x << std::endl << text.getPosition().y << std::endl;
}

gui::~gui()
{
	std::cout<<"deleted gui"<<std::endl;
	delete HPtext;
	delete PAUSEtext;
	delete TITLEtext;
	delete SCOREtext;
	delete m_font;
	delete m_button2;
	delete m_button3;
	delete m_Gmenubutton1;
	delete m_Gmenubutton2;
	delete m_Gmenubutton3;
	delete m_Gmenubutton4;
	delete m_yesbutton;
	delete m_nobutton;
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


	

	for (int i = 0; i < m_buttonTextures.size(); ++i)
	{
		delete m_buttonTextures[i];
	}
}

void gui::update(float DeltaTime)
{
	



	//edit  HP settings
		if( HPnow < 0) 
	{
		HPnow = 0;
	}

	if (m_Play)
	{
		HPtext->setString("HP: Hitpoints " + std::to_string((long double)HPnow) + " / " + std::to_string((long double)HPmax));
		SCOREtext->setString("SCORE:   " + std::to_string((long double)SCORE) );
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

	if (m_returnTitle)
	{
		m_yesbutton->update(DeltaTime);
		m_nobutton->update(DeltaTime);
	}	
	
	
	if (m_menu)
		m_mainbutton1->update(DeltaTime);
		m_mainbutton2->update(DeltaTime);
		m_mainbutton3->update(DeltaTime);
		m_mainbutton4->update(DeltaTime);

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
}

void gui::draw(al::viewport* Viewport)
{
	
	
	if (m_pause)
		Viewport->draw(PAUSEtext);

	if (m_title)
		Viewport->draw(TITLEtext);

	if(m_menu)
	{
		m_mainbutton1->draw(Viewport);
		m_mainbutton2->draw(Viewport);
		m_mainbutton3->draw(Viewport);
		m_mainbutton4->draw(Viewport);
	}
	
	
	if(m_Gmenu)
	{
		
		m_Gmenubutton1->draw(Viewport);
		m_Gmenubutton2->draw(Viewport);
		m_Gmenubutton3->draw(Viewport);
		m_Gmenubutton4->draw(Viewport);
		
	}
	if(m_returnTitle)
	{
		m_yesbutton->draw(Viewport);
		m_nobutton->draw(Viewport);
	}

	if (m_Options)
	{
		m_donebutton->draw(Viewport);
		m_donebutton->draw(Viewport);
		m_plusmusic->draw(Viewport);
		m_plussounds->draw(Viewport);
		m_minusmusic->draw(Viewport);
		m_minussounds->draw(Viewport);
		Viewport->draw(MUSICtext);
		Viewport->draw(SOUNDtext);

		
	}
		
	
	if (m_Play)
	{
		m_button2->draw(Viewport); //button2
		m_button3->draw(Viewport); //button3
		Viewport->draw(HPtext);
		Viewport->draw(SCOREtext);
	}
	if (m_credits)
		m_xbutton->draw(Viewport);
	
	/*if (1)
		m_button2->draw();*/
}

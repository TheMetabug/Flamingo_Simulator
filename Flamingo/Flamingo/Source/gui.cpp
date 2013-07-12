#include "gui.h"

using namespace al;


button::button(al::texture* Texture, al::vector Position, al::input* Input)
{
	m_input = Input;
	m_position = Position;
	setTexture(Texture);
}

button::~button()
{
	delete m_animation;
}

void button::setTexture(al::texture* Texture)
{
	//m_texture.loadTexture(TextureName);
	m_sprite.setTexture(Texture);
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

gui::gui(al::input* Input)
{
	m_input = Input;
	m_pause = false;
	m_title = false;
	m_Play = false;
	m_menu = false;
	m_Gmenu = false;
	m_Options = false;
	m_returnTitle = false;
	
	// HP-basics
	HPmax = 100; //max HP
	HPtaken = 0; // damage/heal
	HPnow = HPmax-HPtaken;


	SCORE= 0;
	
	
	

	



	/*button = "test" button
	button2 = Listbutton
	button3 = mute-button*/

	m_buttonTextures.push_back(new texture("buttons/GameButtons.png")); // 0
	m_button = new button(m_buttonTextures.back(),vector(300,300),m_input);
	m_button->m_sprite.setLayer(296);
	m_button2 = new button(m_buttonTextures.back(),vector(1054,75),m_input);
	m_button2->m_sprite.setLayer(296);
	m_button3 = new button(m_buttonTextures.back(),vector(908,75),m_input);
	m_button3->m_sprite.setLayer(296);

	// GameMenu's buttons
	m_buttonTextures.push_back(new texture("GameMenu/ResumeGame.png")); // 1
	m_Gmenubutton1 = new button(m_buttonTextures.back(),vector(628,331),m_input);
	m_Gmenubutton1->m_sprite.setLayer(299);
	
	m_buttonTextures.push_back(new texture("GameMenu/Restart.png")); // 2
	m_Gmenubutton2 = new button(m_buttonTextures.back(),vector(628,361),m_input);
	m_Gmenubutton2->m_sprite.setLayer(299);
	
	m_buttonTextures.push_back(new texture("GameMenu/Options.png")); // 3
	m_Gmenubutton3 = new button(m_buttonTextures.back(),vector(628,391),m_input);
	m_Gmenubutton3->m_sprite.setLayer(299);
	
	m_buttonTextures.push_back(new texture("GameMenu/ReturnTitle.png")); // 4
	m_Gmenubutton4 = new button(m_buttonTextures.back(),vector(628,421),m_input);
	m_Gmenubutton4->m_sprite.setLayer(299);
	
	m_buttonTextures.push_back(new texture("GameMenu/yesButton.png")); // 5
	m_yesbutton = new button(m_buttonTextures.back(),vector(580,375),m_input);
	m_yesbutton->m_sprite.setLayer(300);
	
	m_buttonTextures.push_back(new texture("GameMenu/noButton.png")); // 6
	m_nobutton = new button(m_buttonTextures.back(),vector(687,375),m_input);
	m_nobutton->m_sprite.setLayer(300);
	
	m_buttonTextures.push_back(new texture("OptionsMenu/Back.png")); // 7
	m_backbutton = new button(m_buttonTextures.back(),vector(575,450),m_input);
	m_backbutton->m_sprite.setLayer(300);
	
	m_buttonTextures.push_back(new texture("OptionsMenu/Apply.png")); // 8
	m_applybutton = new button(m_buttonTextures.back(),vector(700,450),m_input);
	m_applybutton->m_sprite.setLayer(300);


	m_font = new font();

	m_font->loadFromFile("arial.ttf");
	
	
	HPtext = new text("HP-mittari", m_font, 50);
	PAUSEtext = new text(".::pAuSE::.", m_font, 50);
	TITLEtext = new text("Press SPACE",m_font, 50);
	MENUtext = new text("MENU, press button to flamingo", m_font, 50); 
	Gmenutext = new text("GAME MENU", m_font, 50);
	SCOREtext = new text("SCORE", m_font,50);
	
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

	MENUtext->setPosition (vector(550,100));
	MENUtext->setColor(255,0,255, 255);
	MENUtext->setLayer(298);

	Gmenutext->setPosition (vector(550,100));
	Gmenutext->setColor();
	Gmenutext->setLayer(298);
	
	//std::cout << text.getPosition().x << std::endl << text.getPosition().y << std::endl;
}

gui::~gui()
{
	std::cout<<"deleted gui"<<std::endl;
	delete HPtext;
	delete PAUSEtext;
	delete TITLEtext;
	delete MENUtext;
	delete Gmenutext;
	delete SCOREtext;
	delete m_font;
	delete m_button;
	delete m_button2;
	delete m_button3;
	delete m_Gmenubutton1;
	delete m_Gmenubutton2;
	delete m_Gmenubutton3;
	delete m_Gmenubutton4;
	delete m_yesbutton;
	delete m_nobutton;
	delete m_backbutton;
	delete m_applybutton;

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
		m_backbutton->update(DeltaTime);
		m_applybutton->update(DeltaTime);

	}

	if (m_returnTitle)
	{
		m_yesbutton->update(DeltaTime);
		m_nobutton->update(DeltaTime);
	}	
	
	
	if (m_menu)
		m_button->update(DeltaTime);

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
	
}

void gui::draw(al::viewport* Viewport)
{
	
	
	if (m_pause)
		Viewport->draw(PAUSEtext);

	if (m_title)
		Viewport->draw(TITLEtext);

	if(m_menu)
	{
		Viewport->draw(MENUtext);
		m_button->draw(Viewport); //button
	}
	
	
	if(m_Gmenu)
	{
		Viewport->draw(Gmenutext);
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
		m_backbutton->draw(Viewport);
		m_applybutton->draw(Viewport);
	}
		
	
	if (m_Play)
	{
		m_button2->draw(Viewport); //button2
		m_button3->draw(Viewport); //button3
		Viewport->draw(HPtext);
		Viewport->draw(SCOREtext);
	}
	
	/*if (1)
		m_button2->draw();*/
}

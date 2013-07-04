#include "gui.h"

using namespace al;


button::button(std::string TextureName, al::vector Position, al::input* Input)
{
	m_input = Input;
	m_position = Position;
	setTexture(TextureName);
}

button::~button()
{
	delete m_animation;
}

void button::setTexture(std::string TextureName)
{
	m_texture.loadTexture(TextureName);
	m_sprite.setTexture(&m_texture);
	m_animation = new animation(&m_sprite, 1, m_sprite.getTextureSize().x/2, m_sprite.getTextureSize().y/2, false, 0);
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(vector(m_sprite.getSize().x/2, m_sprite.getSize().y/2));
	m_sprite.setScale(1,1);
}

void button::update(float DeltaTime)
{
	m_animation->update(DeltaTime);
	
		if(mouseOver())
		{
			m_animation->ChangeAnimation(1,0,1,100);
		}
		else
			m_animation->ChangeAnimation(0,0,0,100);
}

void button::draw(al::viewport* Viewport)
{
	Viewport->draw(&m_sprite);
}

bool button::isPressed()
{
	if(m_input->isButtonPressed(al::Button::MouseLeft) && mouseOver())
	{			
		m_animation->ChangeAnimation(2,0,2,100);
		return true;
	}
	return false;
}

bool button::mouseOver()
{
	if (m_input->getMousePosition().x > m_position.x - m_sprite.getSize().x/2 &&
		m_input->getMousePosition().x < m_position.x + m_sprite.getSize().x/2 &&
		m_input->getMousePosition().y > m_position.y - m_sprite.getSize().y/2 &&
		m_input->getMousePosition().y < m_position.y + m_sprite.getSize().y/2)
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
	
	// HP-basics
	HPmax = 100; //max HP
	HPtaken = 0; // damage/heal
	HPnow = HPmax-HPtaken;

	/*button = "test" button
	button2 = Listbutton
	button3 = mute-button*/
	m_button = new button("GameButtons.png",vector(300,300),m_input);
	m_button2 = new button("GameButtons.png",vector(1054,75),m_input);
	m_button3 = new button("GameButtons.png",vector(908,75),m_input);

	m_font = new font();

	m_font->loadFromFile("arial.ttf");
	
	// add information what each text does
	HPtext = new text("HP-mittari", m_font, 50);
	PAUSEtext = new text(".::pAuSE::.", m_font, 50);
	TITLEtext = new text("Press SPACE",m_font, 50);
	MENUtext = new text("MENU, press button to flamingo", m_font, 50); 
	Gmenutext = new text("GAME MENU", m_font, 50);
	
	
	HPtext->setColor();
	
	PAUSEtext->setPosition(vector(640, 360));
	PAUSEtext->setOrigin(vector(PAUSEtext->getGlobalBounds().width/2,PAUSEtext->getGlobalBounds().height/2));
	PAUSEtext->setColor();

	TITLEtext->setPosition(vector(550,100));
	TITLEtext->setColor();

	MENUtext->setPosition (vector(550,100));
	MENUtext->setColor();

	Gmenutext->setPosition (vector(550,100));
	Gmenutext->setColor();
	
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
	delete m_font;
	delete m_button;
	delete m_button2;
	delete m_button3;
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
		m_button2->update(DeltaTime);
		m_button3->update(DeltaTime);

	}
	else
		HPtext->setString("");	
		
	
	
	if (m_menu)
		m_button->update(DeltaTime);

	if (m_Play)
	{
		m_button2->update(DeltaTime);
		m_button3->update(DeltaTime);
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
	Viewport->draw(Gmenutext);

	
		
	
	if(m_Play)
	{
		m_button2->draw(Viewport); //button2
		m_button3->draw(Viewport); //button3
		Viewport->draw(HPtext);
	}
	
	/*if (1)
		m_button2->draw();*/
}

#include "gui.h"

using namespace al;


button::button(std::string TextureName, al::vector Position)
{
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
}

void button::draw(al::viewport* Viewport)
{
	Viewport->draw(&m_sprite);
}


gui::gui()
{
	m_pause = false;
	m_title = false;
	m_Play = false;
	m_menu = false;
	m_Gmenu = false;
	
	// HP-basics
	HPmax = 100; //max HP
	HPtaken = 0; // damage/heal
	HPnow = HPmax-HPtaken;

	
	m_button = new button("testbutton.png",vector(300,300));
	//m_button2 = new button(window);

	m_font = new font();

	m_font->loadFromFile("arial.ttf");
	
	// add information what each text does
	HPtext = new text("HP-mittari", m_font, 50);
	PAUSEtext = new text("Pause-teksti", m_font, 50);
	TITLEtext = new text("paina välilyöntiä",m_font, 50);
	MENUtext = new text("Menu-otsikko", m_font, 50); 
	Gmenutext = new text("pelivalikkon otsikko", m_font, 50);
	
	
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
	//delete m_button2;
}

void gui::update(float DeltaTime)
{
	
	//edit  HP settings
		if( HPnow < 0) 
	{
		HPnow = 0;
	}

		if (m_Play)
		HPtext->setString("HP: Hitpoints " + std::to_string((long double)HPnow) + " / " + std::to_string((long double)HPmax));
	else
		HPtext->setString("");	
		
	if (m_pause)
		PAUSEtext->setString(".::pAuSE::.");
	else 
		PAUSEtext->setString("");

	if (m_title)
		TITLEtext->setString("Press SPACE");
	else 
		TITLEtext->setString("");
	
	if (m_menu)
		MENUtext->setString("MENU, press button to flamingo");
	else 
		MENUtext->setString("");

	if (m_Gmenu)
		Gmenutext->setString("GAME MENU");
	else 
		Gmenutext->setString("");
	
	if (m_menu)
		m_button->update(DeltaTime);

	/*if (1)
		m_button2->update(DeltaTime);
*/
	
}

void gui::draw(al::viewport* Viewport)
{
	Viewport->draw(HPtext);
	Viewport->draw(PAUSEtext);
	Viewport->draw(TITLEtext);
	Viewport->draw(MENUtext);
	Viewport->draw(Gmenutext);

	if (m_menu)
		m_button->draw(Viewport);
	
	/*if (1)
		m_button2->draw();*/
}

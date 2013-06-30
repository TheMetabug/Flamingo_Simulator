#include "gui.h"

using namespace al;

gui::gui(sf::RenderWindow* Window)
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

	window = Window;
	
	m_button = new button(window);
	//m_button2 = new button(window);

	font = new sf::Font();

	font->loadFromFile("Assets/arial.ttf");
	
	// add information what each text does
	HPtext = new sf::Text("HP-mittari", *font, 50);
	PAUSEtext = new sf::Text("Pause-teksti",*font, 50);
	TITLEtext = new sf::Text("paina välilyöntiä",* font, 50);
	MENUtext = new sf::Text("Menu-otsikko",*font, 50); 
	Gmenutext = new sf::Text("pelivalikkon otsikko",*font, 50);
	
	
	HPtext->setColor(sf::Color::Red);
	
	PAUSEtext->setPosition(640, 360);
	PAUSEtext->setOrigin(sf::Vector2f(PAUSEtext->getGlobalBounds().width/2,PAUSEtext->getGlobalBounds().height/2));
	PAUSEtext->setColor(sf::Color::Magenta);

	TITLEtext->setPosition(550,100);
	TITLEtext->setColor(sf::Color::Cyan);

	MENUtext->setPosition (550,100);
	MENUtext->setColor(sf::Color::Yellow);

	Gmenutext->setPosition (550,100);
	Gmenutext->setColor(sf::Color::White);
	
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
	delete font;
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
	window->draw(*HPtext);
	window->draw(*PAUSEtext);
	window->draw(*TITLEtext);
	window->draw(*MENUtext);
	window->draw(*Gmenutext);

	if (m_menu)
		m_button->draw(Viewport);
	
	/*if (1)
		m_button2->draw();*/
}


button::button(sf::RenderWindow* Window)
{
	window = Window;

	m_testbuttonPos.x = 300;
	m_testbuttonPos.y = 300;

	m_menuWingPos.x = 50;
	m_menuWingPos.y = 50;

	
	m_testbuttonT = new texture("testbutton.png");
	m_testbuttonS = new sprite(m_testbuttonT);
	m_animation = new animation(m_testbuttonS, 3, 96, 96, false, 0);
	m_testbuttonS->setPosition(m_testbuttonPos);
	m_testbuttonS->setOrigin(sf::Vector2f(m_testbuttonS->getSize().x/2,
						     m_testbuttonS->getSize().y/2));
	m_testbuttonS->setScale(1,1);

	//m_menuWingT = new sf::Texture();
	//m_menuWingT->loadFromFile("Assets/menu_Wing.png");
	//m_menuWingT->setSmooth(true);
	//m_menuWingS = new sf::Sprite();
	//m_menuWingS->setTexture(*m_menuWingT); 
	////m_animation = new animation(m_menuWingS, 3, 96, 96, false, 0);
	//m_menuWingS->setPosition(m_menuWingPos);
	//m_menuWingS->setOrigin(sf::Vector2f(m_menuWingS->getLocalBounds().width/2,
	//					     m_menuWingS->getLocalBounds().height/2));
	//m_menuWingS->setScale(1,1);

}

button::~button()
{

}

void button::update(float DeltaTime)
{
	m_animation->update(DeltaTime);
}

void button::draw(al::viewport* Viewport)
{
	Viewport->addSprite(m_testbuttonS);
	//window->draw(*m_testbuttonS);
	//window->draw(*m_menuWingS);
}

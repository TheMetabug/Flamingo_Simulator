#include "gui.h"



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
	
}

void gui::draw()
{
	window->draw(*HPtext);
	window->draw(*PAUSEtext);
	window->draw(*TITLEtext);
	window->draw(*MENUtext);
	window->draw(*Gmenutext);

	if (m_menu)
		m_button->draw();
}


button::button(sf::RenderWindow* Window)
{
	window = Window;

	m_testbuttonPos.x = 300;
	m_testbuttonPos.y = 300;

	
	m_testbuttonT = new sf::Texture();
	m_testbuttonT->loadFromFile("Assets/testbutton.png");
	m_testbuttonT->setSmooth(true);
	m_testbuttonS = new sf::Sprite();
	m_testbuttonS->setTexture(*m_testbuttonT); 
	m_animation = new animation(m_testbuttonS, 3, 96, 96, false, 0);
	m_testbuttonS->setPosition(m_testbuttonPos);
	m_testbuttonS->setOrigin(sf::Vector2f(m_testbuttonS->getLocalBounds().width/2,
						     m_testbuttonS->getLocalBounds().height/2));
	m_testbuttonS->setScale(1,1);

}

button::~button()
{

}

void button::update(float DeltaTime)
{
	m_animation->update(DeltaTime);
}

void button::draw()
{
	window->draw(*m_testbuttonS);
}

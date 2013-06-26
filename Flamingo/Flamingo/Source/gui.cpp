#include "gui.h"



gui::gui(sf::RenderWindow* Window)
{
	m_pause = false;
	m_title = true;
	m_HP = false;
	
	
	// HP-basics
	HPmax = 100; //max HP
	HPtaken = 0; 
	HPnow = HPmax-HPtaken;

	window = Window;

	font = new sf::Font();

	font->loadFromFile("Assets/arial.ttf");
	
	
	HPtext = new sf::Text("HP-mittari", *font, 50);
	PAUSEtext = new sf::Text("Pause-teksti",*font, 50);
	TITLEtext = new sf::Text("paina välilyöntiä)",* font, 50);
	

	
	HPtext->setColor(sf::Color::Red);
	
	PAUSEtext->setPosition(640, 360);
	PAUSEtext->setOrigin(sf::Vector2f(PAUSEtext->getGlobalBounds().width/2,PAUSEtext->getGlobalBounds().height/2));
	PAUSEtext->setColor(sf::Color::Magenta);

	TITLEtext->setPosition(640,100);
	TITLEtext->setColor(sf::Color::Cyan);

	
	

	//std::cout << text.getPosition().x << std::endl << text.getPosition().y << std::endl;
}

gui::~gui()
{
	std::cout<<"deleted gui"<<std::endl;
	delete HPtext;
	delete PAUSEtext;
	delete TITLEtext;
	delete font;
}

void gui::update(float DeltaTime)
{
	
	//edit  HP settings
		if( HPnow < 0) 
	{
		HPnow = 0;
	}

	

	


	
		if (m_HP)
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
}

void gui::draw()
{
	window->draw(*HPtext);
	window->draw(*PAUSEtext);
	window->draw(*TITLEtext);
}

#include "gui.h"



gui::gui(sf::RenderWindow* Window)
{
	m_pause = false;
	// HP-mittarin tiedot
	HPmax = 100; //max HP
	HPtaken = 0; 
	HPnow = HPmax-HPtaken;

	window = Window;

	font = new sf::Font();

	font->loadFromFile("Assets/arial.ttf");
	HPtext = new sf::Text("", *font, 50);
	PAUSEtext = new sf::Text(".::pAuSE::.",*font, 50);

	PAUSEtext->setPosition(640, 360);
	PAUSEtext->setOrigin(sf::Vector2f(PAUSEtext->getGlobalBounds().width/2,PAUSEtext->getGlobalBounds().height/2));
	PAUSEtext->setColor(sf::Color::Magenta);

	
	HPtext->setColor(sf::Color::Red);

	//std::cout << text.getPosition().x << std::endl << text.getPosition().y << std::endl;
}

gui::~gui()
{
	std::cout<<"deleted gui"<<std::endl;
	delete HPtext;
	delete font;
}

void gui::update(float DeltaTime)
{
	HPtext->setString("HP: Hitpoints " + std::to_string((long double)HPnow) + " / " + std::to_string((long double)HPmax));

		if( HPnow < 0) 
	{
		HPnow = 0;
	}
	
	if (m_pause)
		PAUSEtext->setString(".::pAuSE::.");
	else 
		PAUSEtext->setString("");
}

void gui::draw()
{
	window->draw(*HPtext);
	window->draw(*PAUSEtext);
}

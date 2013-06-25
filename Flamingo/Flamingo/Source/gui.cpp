#include "gui.h"



gui::gui(sf::RenderWindow* Window)
{
	// HP-mittarin tiedot
	HPmax = 100; //max HP
	HPtaken = 0; 
	HPnow = HPmax-HPtaken;

	window = Window;

	font = new sf::Font();

	font->loadFromFile("Assets/arial.ttf");
	HPtext = new sf::Text("", *font, 50);



	



	
	//if (!font.loadFromFile("Assets/arial.ttf"))
	//{
	//	// error...
	//}
	//	// select the font
	//text.setFont(font); // font is a sf::Font

	//// set the string to display
	//text.setString("Hello world");


	//// set the character size
	//text.setCharacterSize(24); // in pixels, not points!

	//set the color
	HPtext->setColor(sf::Color::Red);

	//// set the text style
	//text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	//text.setPosition(50,50);
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
}

void gui::draw()
{
	window->draw(*HPtext);
}

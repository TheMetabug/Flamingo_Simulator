#include "gui.h"



gui::gui(sf::RenderWindow* Window)
{
	window = Window;

	font = new sf::Font();

	font->loadFromFile("Assets/arial.ttf");

	text = new sf::Text("FLAMINGOES", *font, 50);









	
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
	text->setColor(sf::Color::Magenta);

	//// set the text style
	//text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	//text.setPosition(50,50);
	//std::cout << text.getPosition().x << std::endl << text.getPosition().y << std::endl;
}

gui::~gui()
{
	delete text;
	delete font;
}

void gui::update(float DeltaTime)
{
}

void gui::draw()
{
	window->draw(*text);
}

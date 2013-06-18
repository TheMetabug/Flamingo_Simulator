#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <iostream>

class gui
{
public:
	gui(){}
	gui(sf::RenderWindow *Window);
	~gui();
	void update(sf::Time DeltaTime);
	void draw();
	
private:
	sf::RenderWindow *window;



};

#endif
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
	void update(float DeltaTime);
	void draw();
	int HPnow;
	int HPmax;
	int HPtaken;
	bool m_pause;
	bool m_title;
	bool m_HP;
	bool m_menu;
	
private:
	sf::RenderWindow *window;
	sf::Font* font;
	
	sf::Text* HPtext;
	sf::Text* PAUSEtext;
	sf::Text* TITLEtext;
	sf::Text* MENUtext;
};

#endif

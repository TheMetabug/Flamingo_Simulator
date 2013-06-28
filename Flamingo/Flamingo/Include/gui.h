#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "animation.h"


class button
{
public:
	button(){}
	button(sf::RenderWindow *Window);
   ~button();
   	void update(float DeltaTime);
	void draw();
	sf::Vector2f m_testbuttonPos;
	animation *m_animation;

private:
	sf::RenderWindow *window;
	sf::Texture *m_testbuttonT;
	sf::Sprite *m_testbuttonS;
};

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
	bool m_Play;
	bool m_menu;
	bool m_Gmenu;

	button* m_button;

private:
	sf::RenderWindow *window;
	sf::Font* font;
	
	sf::Text* HPtext;
	sf::Text* PAUSEtext;
	sf::Text* TITLEtext;
	sf::Text* MENUtext;
	sf::Text* Gmenutext;

};

#endif

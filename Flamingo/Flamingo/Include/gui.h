#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "animation.h"
#include "program.h"


class button
{
public:
	button(){}
	button(std::string TextureName, al::vector Position);
   ~button();
	void setTexture(std::string TextureName);
   	void update(float DeltaTime);
	void draw(al::viewport* Viewport);

	al::vector m_position;
	animation *m_animation;

private:

	al::texture m_texture;
	al::sprite m_sprite;

};

class gui
{
public:
	gui(){}
	gui(sf::RenderWindow *Window);
	~gui();
	void update(float DeltaTime);
	void draw(al::viewport* Viewport);
	int HPnow;
	int HPmax;
	int HPtaken;
	bool m_pause;
	bool m_title;
	bool m_Play;
	bool m_menu;
	bool m_Gmenu;
	
	button* m_button;
	button* m_button2;

private:
	sf::RenderWindow *window;
	al::font* m_font;
	
	al::text* HPtext;
	al::text* PAUSEtext;
	al::text* TITLEtext;
	al::text* MENUtext;
	al::text* Gmenutext;

};

#endif

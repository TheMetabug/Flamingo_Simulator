#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "animation.h"


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
	sf::Font* font;
	
	sf::Text* HPtext;
	sf::Text* PAUSEtext;
	sf::Text* TITLEtext;
	sf::Text* MENUtext;
	sf::Text* Gmenutext;

};

#endif

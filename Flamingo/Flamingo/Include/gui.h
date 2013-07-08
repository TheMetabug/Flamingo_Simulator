#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "animation.h"
#include "program.h"
#include "input.h"


class button
{
public:
	button(){}
	button(std::string TextureName, al::vector Position, al::input* Input);
   ~button();
	void setTexture(std::string TextureName);
   	void update(float DeltaTime);
	void draw(al::viewport* Viewport);
	bool isPressed();

	al::vector m_position;
	animation *m_animation;
	al::sprite m_sprite;
private:
	bool mouseOver();
	al::input* m_input;

	al::texture m_texture;
	/*al::sprite m_sprite;*/

};
/////////////////////////////////////////////////////////////

class titleCard
{
public:
	titleCard();
	~titleCard();
	void setTexture(std::string TextureName);
   	void update(float DeltaTime);
	void draw(al::viewport* Viewport);
	al::vector m_titlePosition;
	animation *m_titleAnimation;
	al::sprite m_titleSprite;

private:
	al::texture m_texture;
};

////////////////////////////////////////////////////////////
class gui
{
public:
	gui(al::input* Input);
	~gui();
	void update(float DeltaTime);
	void draw(al::viewport* Viewport);
	int HPnow;
	int HPmax;
	int HPtaken;
	int SCORE;
	bool m_pause;
	bool m_title;
	bool m_Play;
	bool m_menu;
	bool m_Gmenu;
	
	button* m_button;
	button* m_button2;
	button* m_button3;

private:
	al::input* m_input;
	al::font* m_font;
	
	al::text* HPtext;
	al::text* PAUSEtext;
	al::text* TITLEtext;
	al::text* MENUtext;
	al::text* Gmenutext;
	al::text* SCOREtext;

	friend class game;
};



#endif

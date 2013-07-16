#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "animation.h"
#include "program.h"
#include "input.h"
#include "sound.h"


class button
{
public:
	button(){}
	button(al::texture* Texture, al::vector Position, al::input* Input, soundLibrary* SoundLibrary);
   ~button();
   void setTexture(al::texture* Texture);
   	void update(float DeltaTime);
	void draw(al::viewport* Viewport);
	bool isPressed();

	al::vector m_position;
	animation *m_animation;
	al::sprite m_sprite;
private:
	bool mouseOver();
	al::input* m_input;

	soundLibrary* m_soundLibrary;

	//al::texture m_texture;
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
	gui(al::input* Input, soundLibrary* SoundLibrary);
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
	bool m_Options;
	bool m_returnTitle;
	
	button* m_button;
	button* m_button2;
	button* m_button3;

	button* m_Gmenubutton1;
	button* m_Gmenubutton2;
	button* m_Gmenubutton3;
	button* m_Gmenubutton4;
	 
	button* m_yesbutton;
	button* m_nobutton;

	button* m_donebutton;
	button* m_plusmusic;
	button* m_minusmusic;
	button* m_plussounds;
	button* m_minussounds;
	


private:
	al::input* m_input;
	al::font* m_font;
	
	al::text* HPtext;
	al::text* PAUSEtext;
	al::text* TITLEtext;
	al::text* MENUtext;
	al::text* Gmenutext;
	al::text* SCOREtext;

	soundLibrary* m_soundLibrary;

	std::vector<al::texture*> m_buttonTextures;




	friend class game;
};



#endif

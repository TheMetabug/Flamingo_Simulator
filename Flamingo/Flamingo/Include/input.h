#ifndef INPUT_H
#define INPUT_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include "program.h"

namespace al
{

const enum Button
{
	MouseLeft,
	MouseRight,
	MouseMiddle
};

//const enum Key
//{
//	Pause,
//	Space,
//	Esc
//};

class input
{
public:
	input(sf::RenderWindow *Window);
	~input();

	
	bool isButtonPressed(Button button);

	//bool isKeyPressed(Key key);
	
	//vector getAbsoluteMousePosition();
	
	vector getMousePosition();
	
	//void setAbsoluteMousePosition(const vector& position);
	
	//void setMousePosition(const vector& position);

	bool active;
private:
	sf::RenderWindow *window;
};

}

#endif
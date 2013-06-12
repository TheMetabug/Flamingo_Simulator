#ifndef INPUT_H
#define INPUT_H

#include <SFML\Graphics.hpp>

class input
{
public:
	input(sf::RenderWindow *Window)
	{
		window = Window;
	}

	~input();

	sf::Mouse::Button;
	//enum Button
 //   {
 //       Left,       ///< The left mouse button
 //       Right,      ///< The right mouse button
 //       Middle,     ///< The middle (wheel) mouse button
 //       XButton1,   ///< The first extra mouse button
 //       XButton2,   ///< The second extra mouse button

 //       ButtonCount ///< Keep last -- the total number of mouse buttons
 //   };

	static bool isButtonPressed(Button button)
	{return sf::Mouse::isButtonPressed(button);}

	static Vector2i getAbsolutePosition()
	{return sf::Mouse::getPosition();}

	static Vector2i getPosition()
	{sf::Mouse::getPosition(*window);}
	
    static void setAbsolutePosition(const Vector2i& position)
	{sf::Mouse::setPosition(position);}
	
    static void setPosition(const Vector2i& position)
	{sf::Mouse::setPosition(position,*window);}

private:
	sf::RenderWindow *window;
};

#endif
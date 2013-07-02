#include "input.h"

using namespace al;

input::input(sf::RenderWindow *Window)
{
	window = Window;
}

input::~input(){}

bool input::isButtonPressed(Button button)
{
	switch (button)
	{
	case MouseLeft:
		return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
		break;
	case MouseRight:
		return sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
		break;
	case MouseMiddle:
		return sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle);
		break;
	default:
		std::cout<<"button not definied"<<std::endl;
		break;
	}

	return false;
}

bool input::isKeyPressed(Key key)
{
	switch (key)
	{
	case Pause:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::P);
		break;
	case Menu:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::M);
		break;
	case Space:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
		break;
	case Esc:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
		break;
	default:
		std::cout<<"key not definied"<<std::endl;
		break;
	}

	return false;
}

//vector input::getAbsoluteMousePosition()
//{
//	return sf::Mouse::getPosition();
//}
	
vector input::getMousePosition()
{
	return sf::Mouse::getPosition(*window);
}
	
//void input::setAbsoluteMousePosition(const vector& position)
//{
//	sf::Vector2i pos(position.x, position.y);
//	sf::Mouse::setPosition(pos);
//}
//	
//void input::setMousePosition(const vector& position)
//{
//	sf::Vector2i pos(position.x, position.y);
//	sf::Mouse::setPosition(pos,*window);
//}
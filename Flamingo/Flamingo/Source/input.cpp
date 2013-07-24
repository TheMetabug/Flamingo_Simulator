#include "input.h"

using namespace al;

input::input(sf::RenderWindow *Window)
	: active(true)
{
	window = Window;
}

input::~input(){}

bool input::isButtonPressed(Button button)
{
	if (active)
	{
		switch (button)
		{
		case MouseLeft:
			return sf::Mouse::isButtonPressed(sf::Mouse::Left);
			break;
		case MouseRight:
			return sf::Mouse::isButtonPressed(sf::Mouse::Right);
			break;
		case MouseMiddle:
			return sf::Mouse::isButtonPressed(sf::Mouse::Middle);
			break;
		default:
#if _DEBUG
			std::cout<<"button not definied"<<std::endl;
#endif
			break;
		}
	}
	return false;
}

//bool input::isKeyPressed(Key key)
//{
//	if (active)
//	{
//		switch (key)
//		{
//		case Pause:
//			return sf::Keyboard::isKeyPressed(sf::Keyboard::P);
//			break;
//		case Space:
//			return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)57);
//			break;
//		case Esc:
//			return sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
//			break;
//		default:
//#if _DEBUG
//			std::cout<<"key not definied"<<std::endl;
//#endif
//			break;
//		}
//	}
//
//	return false;
//}

//vector input::getAbsoluteMousePosition()
//{
//	return sf::Mouse::getPosition();
//}
	
vector input::getMousePosition()
{
	if (active)
	{
		vector retVal(sf::Mouse::getPosition(*window));
		retVal.x /= window->getSize().x/(float)WINDOW_WIDTH;
		retVal.y /= window->getSize().y/(float)WINDOW_HEIGHT;
		return retVal;
	}
	return vector(0,0);
}
	
//void input::setAbsoluteMousePosition(const vector& position)
//{
//	sf::Vector2i pos(position.x, position.y);
//	sf::Mouse::setPosition(pos);
//}
	
void input::setMousePosition(const vector& position)
{
	sf::Vector2i pos(position.x, position.y);
	sf::Mouse::setPosition(pos,*window);
}
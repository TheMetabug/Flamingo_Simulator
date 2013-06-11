#include "game.h"

game::game(sf::RenderWindow *Window)
{
	window = Window;

	drag = 0;
	mouseX,headX,headY,mouseY = 0;
	headOrigin.x = 640;
	headOrigin.y = 360;

	std::cout << "Kirjoitetaanpas kommentti" << std::endl;

	// TEST

		
		testitexture.loadFromFile("image.png");
		sf::Sprite testi(testitexture);
		testi.setPosition(640, 360);
		testi.setOrigin(sf::Vector2f(50, 50));

		sf::Texture crosstexture;
		crosstexture.loadFromFile("crosshair.png");
		sf::Sprite crosshair(crosstexture);
		crosshair.setPosition(640, 360);
		crosshair.setOrigin(sf::Vector2f(25, 25));
}

game::~game()
{
}

void game::update()
{
	// MOUSE

		// HEAD DRAGGIN METHOD
		switch(drag)
		{
			case 0:
					testi.setPosition(640, 360);
				break;

			case 1:
					mousePosition.x = sf::Mouse::getPosition(window).x;
					mousePosition.y = sf::Mouse::getPosition(window).y;

					testi.setPosition(mousePosition);
					
					headPosition.x = testi.getPosition().x;
					headPosition.y = testi.getPosition().y;

				break;

			case 2:
				{
				sf::Vector2f Direction(headOrigin - headPosition);
				sf::Vector2f Movement(Direction.x/15,Direction.y/15);
				headPosition += Movement;

				testi.setPosition(headPosition);
				}

				if(testi.getPosition().x == headPosition.x, testi.getPosition().y == headPosition.y)
				drag = 0;

				break;
		}

		// MOUSE INPUT

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
		sf::Mouse::getPosition(window).x > testi.getPosition().x - 50 &&
		sf::Mouse::getPosition(window).x < testi.getPosition().x + 50 &&
		sf::Mouse::getPosition(window).y > testi.getPosition().y - 50 &&
		sf::Mouse::getPosition(window).y < testi.getPosition().y + 50)
		{
			drag = 1;
		}
		else
		{	
			drag = 0;
			if(testi.getPosition().x != 640 && testi.getPosition().y != 360)
				drag = 2;
		}
}
void game::draw()
{
	window->draw(testi);
	window->draw(crosshair);
}
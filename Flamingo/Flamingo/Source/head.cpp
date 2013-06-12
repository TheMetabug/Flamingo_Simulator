#include "head.h"
head::head(sf::RenderWindow *Window)
{
	window = Window;

	drag = 0;
	headOrigin.x = 640;
	headOrigin.y = 360;

	headTexture = new sf::Texture();
	headTexture->loadFromFile("image.png");
	flamingoHead.setTexture(*headTexture);
	flamingoHead.setPosition(640, 360);
	flamingoHead.setOrigin(sf::Vector2f(50, 50));

	crosstexture = new sf::Texture();	
	crosstexture->loadFromFile("crosshair.png");
	crosshair.setTexture(*crosstexture);
	crosshair.setPosition(640, 360);
	crosshair.setOrigin(sf::Vector2f(25, 25));

}

head::~head()
{
}

void head::update(sf::Time DeltaTime)
{
			switch(drag)
		{
			case 0:
				flamingoHead.setPosition(640, 360);
				break;

			case 1:
				mousePosition.x = sf::Mouse::getPosition(*window).x;
				mousePosition.y = sf::Mouse::getPosition(*window).y;

				flamingoHead.setPosition(mousePosition);

				headPosition.x = flamingoHead.getPosition().x;
				headPosition.y = flamingoHead.getPosition().y;

				break;

			case 2:
				{
				sf::Vector2f Direction(headOrigin - headPosition);
				sf::Vector2f Movement(Direction.x/15,Direction.y/15);
				headPosition += Movement;

				flamingoHead.setPosition(headPosition);
				}

				if(headPosition.x == 640, headPosition.y == 320)
				drag = 0;

				break;
		}

		// MOUSE INPUT

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
			sf::Mouse::getPosition(*window).x > flamingoHead.getPosition().x - 50 &&
			sf::Mouse::getPosition(*window).x < flamingoHead.getPosition().x + 50 &&
			sf::Mouse::getPosition(*window).y > flamingoHead.getPosition().y - 50 &&
			sf::Mouse::getPosition(*window).y < flamingoHead.getPosition().y + 50 )
		{
			if(drag == 0)
			drag = 1;
		}
		else
		{	
			drag = 0;
			if(flamingoHead.getPosition().x != 640 && flamingoHead.getPosition().y != 360)
				drag = 2;
		}

}

void head::draw()
{
	window->draw(flamingoHead);
	window->draw(crosshair);
}
#include "flamingo.h"


flamingo::flamingo(sf::RenderWindow *Window, collision* Collide)
{
	window = Window;

	////////HEAD/////////

	drag = 0;
	headOrigin.x = 721;
	headOrigin.y = 385;

	h_rotate = 0;

	headTexture = new sf::Texture();
	headTexture->loadFromFile("Assets/FlamingoEmo_Head.png");
	headTexture->setSmooth(true);
	flamingoHead.setTexture(*headTexture);
	flamingoHead.setPosition(headOrigin);
	flamingoHead.setOrigin(sf::Vector2f(311, 128));
	flamingoHead.setScale(0.3f, 0.3f);
	

	crossTexture = new sf::Texture();	
	crossTexture->loadFromFile("Assets/crosshair.png");
	crossTexture->setSmooth(true);
	crosshairSprite.setTexture(*crossTexture);
	crosshairSprite.setPosition(headOrigin);
	crosshairSprite.setOrigin(sf::Vector2f(25, 25));

	headHitbox = Collide->createHitBox(headPosition, flamingoHead.getTexture()->getSize(), sf::Vector2f(311, 128), true);

	/////////NECK///////

	
	neckOrigin.x = 740;
	neckOrigin.y = 550;

	neckTexture = new sf::Texture();
	neckTexture->loadFromFile("Assets/FlamingoEmo_Neck.png");
	neckTexture->setSmooth(true);
	flamingoNeck.setTexture(*neckTexture);
	flamingoNeck.setPosition(neckOrigin);
	flamingoNeck.setOrigin(sf::Vector2f(302, 774));
	flamingoNeck.setScale(0.3f, 0.3f);

	/////////BODY//////////

	bodyOrigin.x = 740;
	bodyOrigin.y = 550;

	bodyTexture = new sf::Texture();
	bodyTexture->loadFromFile("Assets/FlamingoEmo_Body.png");
	bodyTexture->setSmooth(true);
	flamingoBody.setTexture(*bodyTexture);
	flamingoBody.setPosition(bodyOrigin);
	flamingoBody.setOrigin(sf::Vector2f(266, 368));
	flamingoBody.setScale(0.3f, 0.3f);
}

flamingo::~flamingo()
{
	std::cout<<"deleted flamingo"<<std::endl;
}

void flamingo::update(float DeltaTime)
{
			switch(drag)
		{
			case 0: // head in origin
				headPosition = headOrigin;
				break;

			case 1: // head being dragged
				mousePosition.x = sf::Mouse::getPosition(*window).x;
				mousePosition.y = sf::Mouse::getPosition(*window).y;

				headPosition = mousePosition;

				{
					sf::Vector2f Direction(headOrigin - headPosition);
					float multiplier = 3.0f;

					//cant drag head too far away.
					float distance = sqrt(pow(Direction.x,2) + pow(Direction.y,2));

					// count where head will be when we add multiplier to it
					if (distance > 100)
					{
						float multiplier = distance/100;
						Direction.x /= multiplier;
						Direction.y /= multiplier;
					}

					//std::cout<<distance<<std::endl;
					
					headPosition = headOrigin - Direction;

					// crosshair goes opposite direction of the head from the origin
					crossHair = headOrigin + sf::Vector2f(Direction.x * multiplier, Direction.y * multiplier);
					crosshairSprite.setPosition(crossHair);

					// count angle from headposition and headposition.x
					h_rotate = 0 ;
				}
				break;

			case 2: // head released, goes to crosshair
				{
				sf::Vector2f Direction(crossHair - headPosition);
				sf::Vector2f Movement((Direction.x*10)*DeltaTime,(Direction.y*10)*DeltaTime);
				headPosition += Movement;
				}

				//std::cout << "X: " << headPosition.x << std::endl << "Y: " << headPosition.y << std::endl;

				//check if head gets back to start position
				if(headPosition.x < crossHair.x+4 && headPosition.x > crossHair.x-4 &&
					headPosition.y < crossHair.y+4 && headPosition.y > crossHair.y-4)
				{
					drag = 3;
				}
				break;
			case 3: //head goes back to starting point/origin
				{
				sf::Vector2f Direction(headOrigin - headPosition);
				sf::Vector2f Movement((Direction.x*10)*DeltaTime,(Direction.y*10)*DeltaTime);
				headPosition += Movement;
				}

				if(headPosition.x < headOrigin.x+1 && headPosition.x > headOrigin.x-1 &&
					headPosition.y < headOrigin.y+1 && headPosition.y > headOrigin.y-1)
				{
					drag = 0;
					crossHair = headOrigin;
				}
				break;
		}

		// MOUSE INPUT

		// check if 
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
			sf::Mouse::getPosition(*window).x > flamingoHead.getPosition().x - 50 &&
			sf::Mouse::getPosition(*window).x < flamingoHead.getPosition().x + 50 &&
			sf::Mouse::getPosition(*window).y > flamingoHead.getPosition().y - 50 &&
			sf::Mouse::getPosition(*window).y < flamingoHead.getPosition().y + 50 )
		{
			if(drag == 0)
			drag = 1;
		}
		else if (drag == 1)
		{	
			// if(flamingoHead.getPosition().x != 640 && flamingoHead.getPosition().y != 360)
			if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
				drag = 2;
		}

		// set sprites to their Positions
		flamingoHead.setPosition(headPosition);
		crosshairSprite.setPosition(crossHair);
}

void flamingo::draw()
{
	window->draw(flamingoNeck);
	window->draw(flamingoHead);
	window->draw(crosshairSprite);
	window->draw(flamingoBody);
}
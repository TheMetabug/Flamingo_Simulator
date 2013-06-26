#include "flamingo.h"


flamingo::flamingo(sf::RenderWindow *Window, collision* Collide)
{
	window = Window;

	////////HEAD/////////
	drag = 0;
	headOrigin.x = 721;
	headOrigin.y = 385;
	h_rotate = 0;

	
	/////////NECK///////
	neckOrigin.x = 740;
	neckOrigin.y = 550;
	

	/////////BODY//////////
	bodyOrigin.x = 740;
	bodyOrigin.y = 550;

	
	// Textures and sprites
#if 1

	headTexture = new sf::Texture();
	headTexture->loadFromFile("Assets/Flamingo_player_head.png");
	headTexture->setSmooth(true);
	flamingoHead.setTexture(*headTexture);
	flamingoHead.setPosition(headOrigin);
	flamingoHead.setOrigin(sf::Vector2f(120, 70));
	flamingoHead.setScale(0.5f, 0.5f);

	crossTexture = new sf::Texture();	
	crossTexture->loadFromFile("Assets/crosshair.png");
	crossTexture->setSmooth(true);
	crosshairSprite.setTexture(*crossTexture);
	crosshairSprite.setPosition(headOrigin);
	crosshairSprite.setOrigin(sf::Vector2f(25, 25));

	neckTexture = new sf::Texture();
	neckTexture->loadFromFile("Assets/Flamingo_player_neck.png");
	neckTexture->setSmooth(true);
	flamingoNeck.setTexture(*neckTexture);
	flamingoNeck.setPosition(neckOrigin);
	flamingoNeck.setOrigin(sf::Vector2f(18, 20));
	flamingoNeck.setScale(0.5f, 0.5f);


	bodyTexture = new sf::Texture();
	bodyTexture->loadFromFile("Assets/Flamingo_player_body.png");
	bodyTexture->setSmooth(true);
	flamingoBody.setTexture(*bodyTexture);
	flamingoBody.setPosition(bodyOrigin);
	flamingoBody.setOrigin(sf::Vector2f(10, 100));
	flamingoBody.setScale(0.5f, 0.5f);
#endif
	
	float HBW = flamingoHead.getGlobalBounds().width / 2;
	float HBH = flamingoHead.getGlobalBounds().width / 2;
	float HBOX = ((flamingoHead.getOrigin().x - 60) * flamingoHead.getScale().x) + HBW/2;
	float HBOY = ((flamingoHead.getOrigin().y - 80) * flamingoHead.getScale().y) + HBH/2;

	headHitbox = Collide->createHitBox(headPosition, 
		sf::Vector2f(HBW,HBH), 
		sf::Vector2f(HBOX,HBOY),1);
}

flamingo::~flamingo()
{
	std::cout<<"deleted flamingo"<<std::endl;
	delete bodyTexture;
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
		headHitbox->Position = headPosition;
}

void flamingo::draw()
{
	window->draw(flamingoNeck);
	window->draw(flamingoHead);
	window->draw(crosshairSprite);
	window->draw(flamingoBody);
}
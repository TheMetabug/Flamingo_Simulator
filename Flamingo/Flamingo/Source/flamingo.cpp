#include "flamingo.h"
#define PI 3.14159265358979323846264


flamingo::flamingo(sf::RenderWindow *Window, collision* Collide)
{
	window = Window;

	/////////BODY//////////
	m_flamingoPosition = sf::Vector2f(740,550);

	////////HEAD/////////
	drag = 0;
	headOrigin = m_flamingoPosition + sf::Vector2f(-19,-165);
	h_rotate = 0;

	
	// Textures and sprites
#if 1

	///////////BODY////////////
	bodyTexture = new sf::Texture();
	bodyTexture->loadFromFile("Assets/Flamingo_player_body.png");
	bodyTexture->setSmooth(true);
	flamingoBody.setTexture(*bodyTexture);
	flamingoBody.setPosition(m_flamingoPosition);
	flamingoBody.setOrigin(sf::Vector2f(10, 100));
	flamingoBody.setScale(0.5f, 0.5f);

	////////////HEAD///////////
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

	/////////////NECK//////////
	neckTexture = new sf::Texture();
	neckTexture->loadFromFile("Assets/Flamingo_player_neck.png");
	neckTexture->setSmooth(true);

	
#endif

	/////////NECK///////

	int neckPieceCount = 10;
	for (int i = 0; i < neckPieceCount; ++i)
	{
		m_neckPieces.push_back(neckPiece());
		m_neckPieces[i].m_sprite.setTexture(*neckTexture);
		m_neckPieces[i].m_sprite.setPosition(m_flamingoPosition + sf::Vector2f(-1*i,-17*i));
		m_neckPieces[i].m_sprite.setOrigin(sf::Vector2f(18, 20));
		m_neckPieces[i].m_sprite.setScale(0.5f, 0.5f);

		float place = ((float)i + 0.5f)/(float)neckPieceCount;
		m_neckPieces[i].m_positionMultiplier = sf::Vector2f(place,(sin(float(place * -2 * PI))));
	}


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
	m_bodyToHead = m_flamingoPosition - headPosition;

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
				if (distance > 1000)
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

	//////////NECK///////////////
#if 1
	{
		float lenght = sqrt(pow(m_bodyToHead.x,2) + pow(m_bodyToHead.y,2));
		float angle = ((atan(m_bodyToHead.y/m_bodyToHead.x))/(PI*2))*360.0f;
		sf::Transform transform;
		if (m_bodyToHead.x < 0)
			transform.rotate(angle);
		else
			transform.rotate(angle+180);

		std::cout<<"x "<<m_bodyToHead.x<<" y "<<m_bodyToHead.y<<"lenght "<<lenght<<" angle "<<angle<<std::endl;

		for (int i = 0; i < m_neckPieces.size(); ++i)
		{
			m_neckPieces[i].m_positionRelative = sf::Vector2f(
				m_neckPieces[i].m_positionMultiplier.x * lenght,
				m_neckPieces[i].m_positionMultiplier.y * lenght/8);

			m_neckPieces[i].m_positionRelative = transform.transformPoint(m_neckPieces[i].m_positionRelative);
			m_neckPieces[i].m_sprite.setPosition(m_neckPieces[i].m_positionRelative + m_flamingoPosition);
		}
	}
#endif


	// set sprites to their Positions
	flamingoHead.setPosition(headPosition);
	crosshairSprite.setPosition(crossHair);
	headHitbox->Position = headPosition;
}

void flamingo::draw()
{
	window->draw(flamingoBody);
	for (int i = 0; i < m_neckPieces.size(); ++i)
		window->draw(m_neckPieces[i].m_sprite);
	window->draw(flamingoHead);
	window->draw(crosshairSprite);
}
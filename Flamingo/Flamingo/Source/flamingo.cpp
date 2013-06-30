#include "flamingo.h"
#define PI 3.14159265358979323846264


flamingo::flamingo(sf::RenderWindow *Window, collision* Collide)
{
	window = Window;

	/////////BODY//////////
	m_flamingoPosition = sf::Vector2f(740,550);

	////////HEAD/////////
	m_drag = 0;
	m_headOrigin = m_flamingoPosition + sf::Vector2f(-19,-165);
	m_headRotate = 0;

	
	// Textures and sprites
#if 1

	///////////BODY////////////
	m_bodyTexture = new sf::Texture();
	m_bodyTexture->loadFromFile("Assets/Flamingo_player_body.png");
	m_bodyTexture->setSmooth(true);
	m_flamingoBody.setTexture(*m_bodyTexture);
	m_flamingoBody.setPosition(m_flamingoPosition);
	m_flamingoBody.setOrigin(sf::Vector2f(10, 100));
	m_flamingoBody.setScale(0.5f, 0.5f);

	////////////HEAD///////////
	m_headTexture = new sf::Texture();
	m_headTexture->loadFromFile("Assets/Flamingo_player_head.png");
	m_headTexture->setSmooth(true);
	m_flamingoHead.setTexture(*m_headTexture);
	m_flamingoHead.setPosition(m_headOrigin);
	m_flamingoHead.setOrigin(sf::Vector2f(120, 70));
	m_flamingoHead.setScale(0.5f, 0.5f);

	sf::Rect<float> asdf = m_flamingoHead.getGlobalBounds();

	m_crossTexture = new sf::Texture();	
	m_crossTexture->loadFromFile("Assets/crosshair.png");
	m_crossTexture->setSmooth(true);
	m_crosshairSprite.setTexture(*m_crossTexture);
	m_crosshairSprite.setPosition(m_headOrigin);
	m_crosshairSprite.setOrigin(sf::Vector2f(25, 25));

	/////////////NECK//////////
	m_neckTexture = new sf::Texture();
	m_neckTexture->loadFromFile("Assets/Flamingo_player_neck.png");
	m_neckTexture->setSmooth(true);

	
#endif

	/////////NECK///////

	int neckPieceCount = 10;
	for (int i = 0; i < neckPieceCount; ++i)
	{
		m_neckPieces.push_back(neckPiece());
		m_neckPieces[i].m_sprite.setTexture(*m_neckTexture);
		m_neckPieces[i].m_sprite.setPosition(m_flamingoPosition + sf::Vector2f(-1*i,-17*i));
		m_neckPieces[i].m_sprite.setOrigin(sf::Vector2f(18, 20));
		m_neckPieces[i].m_sprite.setScale(0.5f, 0.5f);

		float place = ((float)i + 0.5f)/(float)neckPieceCount;
		m_neckPieces[i].m_positionMultiplier = sf::Vector2f(place,(sin(float(place * -2 * PI))));
	}


	float HBW = m_flamingoHead.getGlobalBounds().width / 2;
	float HBH = m_flamingoHead.getGlobalBounds().width / 2;
	float HBOX = ((m_flamingoHead.getOrigin().x - 60) * m_flamingoHead.getScale().x) + HBW/2;
	float HBOY = ((m_flamingoHead.getOrigin().y - 80) * m_flamingoHead.getScale().y) + HBH/2;

	m_headHitbox = Collide->createHitBox(m_headPosition, 
		sf::Vector2f(HBW,HBH), 
		sf::Vector2f(HBOX,HBOY),1);
}

flamingo::~flamingo()
{
	std::cout<<"deleted flamingo"<<std::endl;
	delete m_bodyTexture;
}

void flamingo::update(float DeltaTime)
{
	m_bodyToHead = m_flamingoPosition - m_headPosition;

		switch(m_drag)
	{
		case 0: // head in origin
			m_headPosition = m_headOrigin;
			break;

		case 1: // head being dragged
			m_mousePosition.x = sf::Mouse::getPosition(*window).x;
			m_mousePosition.y = sf::Mouse::getPosition(*window).y;

			m_headPosition = m_mousePosition;

			{
				sf::Vector2f Direction(m_headOrigin - m_headPosition);
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
					
				m_headPosition = m_headOrigin - Direction;

				// crosshair goes opposite direction of the head from the origin
				m_crossHair = m_headOrigin + sf::Vector2f(Direction.x * multiplier, Direction.y * multiplier);
				m_crosshairSprite.setPosition(m_crossHair);

				// count angle from headposition and headposition.x
				m_headRotate = 0 ;
			}
			break;

		case 2: // head released, goes to crosshair
			{
			sf::Vector2f Direction(m_crossHair - m_headPosition);
			sf::Vector2f Movement((Direction.x*10)*DeltaTime,(Direction.y*10)*DeltaTime);
			m_headPosition += Movement;
			}

			//std::cout << "X: " << headPosition.x << std::endl << "Y: " << headPosition.y << std::endl;

			//check if head gets back to start position
			if(m_headPosition.x < m_crossHair.x+4 && m_headPosition.x > m_crossHair.x-4 &&
				m_headPosition.y < m_crossHair.y+4 && m_headPosition.y > m_crossHair.y-4)
			{
				m_drag = 3;
			}
			break;
		case 3: //head goes back to starting point/origin
			{
				sf::Vector2f Direction(m_headOrigin - m_headPosition);
				sf::Vector2f Movement((Direction.x*10)*DeltaTime,(Direction.y*10)*DeltaTime);
				m_headPosition += Movement;
			}

			if(m_headPosition.x < m_headOrigin.x+1 && m_headPosition.x > m_headOrigin.x-1 &&
				m_headPosition.y < m_headOrigin.y+1 && m_headPosition.y > m_headOrigin.y-1)
			{
				m_drag = 0;
				m_crossHair = m_headOrigin;
			}
			break;
	}

	// MOUSE INPUT

	// check if 
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
		sf::Mouse::getPosition(*window).x > m_flamingoHead.getPosition().x - 50 &&
		sf::Mouse::getPosition(*window).x < m_flamingoHead.getPosition().x + 50 &&
		sf::Mouse::getPosition(*window).y > m_flamingoHead.getPosition().y - 50 &&
		sf::Mouse::getPosition(*window).y < m_flamingoHead.getPosition().y + 50 )
	{
		if(m_drag == 0)
		m_drag = 1;
	}
	else if (m_drag == 1)
	{	
		// if(flamingoHead.getPosition().x != 640 && flamingoHead.getPosition().y != 360)
		if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			m_drag = 2;
	}

	//////////NECK///////////////
#if 1
	{
		float lenght = sqrt(pow(m_bodyToHead.x,2) + pow(m_bodyToHead.y,2));
		float angle = atan(m_bodyToHead.y/m_bodyToHead.x)*(180.0f/PI);
		sf::Transform transform;
		if (m_bodyToHead.x < 0)
			transform.rotate(angle);
		else
			transform.rotate(angle+180);

		//std::cout<<"x "<<m_bodyToHead.x<<" y "<<m_bodyToHead.y<<"lenght "<<lenght<<" angle "<<angle<<std::endl;

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
	m_flamingoHead.setPosition(m_headPosition);
	m_crosshairSprite.setPosition(m_crossHair);
	m_headHitbox->Position = m_headPosition;
}

void flamingo::draw()
{
	window->draw(m_flamingoBody);
	for (int i = 0; i < m_neckPieces.size(); ++i)
		window->draw(m_neckPieces[i].m_sprite);
	window->draw(m_flamingoHead);
	window->draw(m_crosshairSprite);
}
#include "nest.h"

nest::nest(sf::RenderWindow *Window, collision* Collide)
{
	// nest
	m_nestPosition = sf::Vector2f(200, 600);
	m_hatchlingPositions.push_back( sf::Vector2f(m_nestPosition.x, m_nestPosition.y - 60));
	m_hatchlingPositions.push_back( sf::Vector2f(m_nestPosition.x - 60, m_nestPosition.y - 30));
	m_hatchlingPositions.push_back( sf::Vector2f(m_nestPosition.x + 60, m_nestPosition.y - 30));
	window = Window;
	m_nestTexture = new sf::Texture();
	m_nestTexture->loadFromFile("Assets/NEST.png");
	m_nestTexture->setSmooth(true);
	m_flamingonest.setTexture(*m_nestTexture);
	m_flamingonest.setPosition(m_nestPosition);
	m_flamingonest.setOrigin(sf::Vector2f(m_flamingonest.getLocalBounds().width/2,
						   m_flamingonest.getLocalBounds().height/2));
	m_flamingonest.setScale(1,1);

	m_nestHitbox = Collide->createHitBox(m_nestPosition,
		sf::Vector2f(m_flamingonest.getGlobalBounds().width,
					 m_flamingonest.getGlobalBounds().height), 
		sf::Vector2f(m_flamingonest.getGlobalBounds().width/2,
					 m_flamingonest.getGlobalBounds().height/2),
		0);

	///// hatchling 1 /////

	for (int i = 0; i < 3; ++i)
	{

		m_hatchlingTextures.push_back( new sf::Texture());
	m_hatchlingTextures[i]->loadFromFile("Assets/Hatchling.png");
	m_hatchlingTextures[i]->setSmooth(true);
	m_hatchlings.push_back( new sf::Sprite());
	m_hatchlings[i]->setTexture(*m_hatchlingTextures[i]);
	m_hatchlings[i]->setPosition(m_hatchlingPositions[i]);
	m_hatchlings[i]->setOrigin(sf::Vector2f(m_hatchlings[i]->getLocalBounds().width/2,
						   m_hatchlings[i]->getLocalBounds().height/2));
	m_hatchlings[i]->setScale(0.5f,0.5f);

	m_hatchlingHitboxes.push_back( Collide->createHitBox(m_hatchlingPositions[i],
		sf::Vector2f(m_hatchlings[i]->getGlobalBounds().width,
						m_hatchlings[i]->getGlobalBounds().height), 
		sf::Vector2f(m_hatchlings[i]->getGlobalBounds().width/2,
						m_hatchlings[i]->getGlobalBounds().height/2),
		0));
	}

	////// hatchling 2 ////

	//m_hatchlingTexture_2 = new sf::Texture();
	//m_hatchlingTexture_2->loadFromFile("Assets/Hatchling.png");
	//m_hatchlingTexture_2->setSmooth(true);
	//m_hatchling_2 = new sf::Sprite();
	//m_hatchling_2->setTexture(*m_hatchlingTexture_2);
	//m_hatchling_2->setPosition(m_hatchlingPosition_2);
	//m_hatchling_2->setOrigin(sf::Vector2f(m_hatchling_2->getLocalBounds().width/2,
	//					   m_hatchling_2->getLocalBounds().height/2));
	//m_hatchling_2->setScale(0.5f,0.5f);

	//m_hatchlingHitbox = Collide->createHitBox(m_hatchlingPosition_2,
	//	sf::Vector2f(m_hatchling_2->getGlobalBounds().width,
	//					m_hatchling_2->getGlobalBounds().height), 
	//	sf::Vector2f(m_hatchling_2->getGlobalBounds().width/2,
	//					m_hatchling_2->getGlobalBounds().height/2),
	//	0);
	//	
	////// hatchling 3 ////

	//m_hatchlingTexture_3 = new sf::Texture();
	//m_hatchlingTexture_3->loadFromFile("Assets/Hatchling.png");
	//m_hatchlingTexture_3->setSmooth(true);
	//m_hatchling_3 = new sf::Sprite();
	//m_hatchling_3->setTexture(*m_hatchlingTexture_3);
	//m_hatchling_3->setPosition(m_hatchlingPosition_3);
	//m_hatchling_3->setOrigin(sf::Vector2f(m_hatchling_3->getLocalBounds().width/2,
	//					   m_hatchling_3->getLocalBounds().height/2));
	//m_hatchling_3->setScale(0.5f,0.5f);

	//m_hatchlingHitbox = Collide->createHitBox(m_hatchlingPosition_3,
	//	sf::Vector2f(m_hatchling_3->getGlobalBounds().width,
	//					m_hatchling_3->getGlobalBounds().height), 
	//	sf::Vector2f(m_hatchling_3->getGlobalBounds().width/2,
	//					m_hatchling_3->getGlobalBounds().height/2),
	//	0);
}
nest::~nest()
{
	std::cout<<"deleted nest"<<std::endl;
}
void nest::update(float DeltaTime)
{
	//m_nestHitbox->Position = m_nestPosition;
}
void nest::draw()
{
	window->draw(m_flamingonest);
	for (int i = 0; i < m_hatchlings.size(); ++i)
		window->draw(*m_hatchlings[i]);
}
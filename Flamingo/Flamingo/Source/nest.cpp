#include "nest.h"

nest::nest(sf::RenderWindow *Window, collision* Collide)
{
	// nest
	m_nestPosition = sf::Vector2f(200, 600);
	m_hatchlingPosition = sf::Vector2f(m_nestPosition.x, m_nestPosition.y - 60);
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

	// hatchling

	m_hatchlingTexture = new sf::Texture();
	m_hatchlingTexture->loadFromFile("Assets/Hatchling.png");
	m_hatchlingTexture->setSmooth(true);
	m_hatchling = new sf::Sprite();
	m_hatchling->setTexture(*m_hatchlingTexture);
	m_hatchling->setPosition(m_hatchlingPosition);
	m_hatchling->setOrigin(sf::Vector2f(m_hatchling->getLocalBounds().width/2,
						   m_hatchling->getLocalBounds().height/2));
	m_hatchling->setScale(0.5f,0.5f);

	m_hatchlingHitbox = Collide->createHitBox(m_hatchlingPosition,
		sf::Vector2f(m_hatchling->getGlobalBounds().width,
						m_hatchling->getGlobalBounds().height), 
		sf::Vector2f(m_hatchling->getGlobalBounds().width/2,
						m_hatchling->getGlobalBounds().height/2),
		0);
		
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
	window->draw(*m_hatchling);
}
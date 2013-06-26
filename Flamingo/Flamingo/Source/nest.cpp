#include "nest.h"

nest::nest(sf::RenderWindow *Window, collision* Collide)
{
	// nest
	nestPosition = sf::Vector2f(200, 600);
	hatchlingPosition = sf::Vector2f(nestPosition.x, nestPosition.y - 60);
	window = Window;
	nestTexture = new sf::Texture();
	nestTexture->loadFromFile("Assets/NEST.png");
	nestTexture->setSmooth(true);
	flamingonest.setTexture(*nestTexture);
	flamingonest.setPosition(nestPosition);
	flamingonest.setOrigin(sf::Vector2f(flamingonest.getLocalBounds().width/2,
						   flamingonest.getLocalBounds().height/2));
	flamingonest.setScale(1,1);

	nestHitbox = Collide->createHitBox(nestPosition,
		sf::Vector2f(flamingonest.getGlobalBounds().width,
					 flamingonest.getGlobalBounds().height), 
		sf::Vector2f(flamingonest.getGlobalBounds().width/2,
					 flamingonest.getGlobalBounds().height/2),
		0);

	// hatchling

	m_hatchlingTexture = new sf::Texture();
	m_hatchlingTexture->loadFromFile("Assets/Hatchling.png");
	m_hatchlingTexture->setSmooth(true);
	m_hatchling = new sf::Sprite();
	m_hatchling->setTexture(*m_hatchlingTexture);
	m_hatchling->setPosition(hatchlingPosition);
	m_hatchling->setOrigin(sf::Vector2f(m_hatchling->getLocalBounds().width/2,
						   m_hatchling->getLocalBounds().height/2));
	m_hatchling->setScale(0.5f,0.5f);

	hatchlingHitbox = Collide->createHitBox(hatchlingPosition,
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
	//nestHitbox->Position = nestPosition;
}
void nest::draw()
{
	window->draw(flamingonest);
	window->draw(*m_hatchling);
}
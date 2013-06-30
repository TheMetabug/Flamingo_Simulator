#include "nest.h"

using namespace al;

nest::nest(sf::RenderWindow *Window, collision* Collide)
{
	window = Window;

	///// nest //////
	m_nestPosition = sf::Vector2f(200, 600);

	// create texture,sprite, positions etc
	m_nestTexture = new sf::Texture();
	m_nestTexture->loadFromFile("Assets/NEST.png");
	m_nestTexture->setSmooth(true);
	m_flamingonest.setTexture(*m_nestTexture);
	m_flamingonest.setPosition(m_nestPosition);
	m_flamingonest.setOrigin(sf::Vector2f(m_flamingonest.getLocalBounds().width/2,
						     m_flamingonest.getLocalBounds().height/2));
	m_flamingonest.setScale(1,1);

	// hitbox
	m_nestHitbox = Collide->createHitBox(m_nestPosition,
		sf::Vector2f(m_flamingonest.getGlobalBounds().width,
					 m_flamingonest.getGlobalBounds().height), 
		sf::Vector2f(m_flamingonest.getGlobalBounds().width/2,
					 m_flamingonest.getGlobalBounds().height/2),
		0);

	///// hatchlings /////

	m_hatchlingPositions.push_back( sf::Vector2f(m_nestPosition.x, m_nestPosition.y - 60));
	m_hatchlingPositions.push_back( sf::Vector2f(m_nestPosition.x - 60, m_nestPosition.y - 30));
	m_hatchlingPositions.push_back( sf::Vector2f(m_nestPosition.x + 60, m_nestPosition.y - 30));

	m_hatchlingTexture = new texture("Hatchling_sheet.png");

	for (int i = 0; i < 3; ++i)
	{
		// create texture,sprite, positions etc
		m_hatchlings.push_back( new sprite(m_hatchlingTexture));
		m_animations.push_back(new animation(m_hatchlings[i], 3, 256, 256, false, 7));
		m_hatchlings[i]->setPosition(m_hatchlingPositions[i]);
		m_hatchlings[i]->setOrigin(sf::Vector2f(m_hatchlings[i]->getSize().x/2,
							   m_hatchlings[i]->getSize().y/2));
		m_hatchlings[i]->setScale(0.5f,0.5f);

		//animation

		//hitbox
		m_hatchlingHitboxes.push_back( Collide->createHitBox(m_hatchlingPositions[i],
			sf::Vector2f(m_hatchlings[i]->getTransformedSize().x,
							m_hatchlings[i]->getTransformedSize().y), 
			sf::Vector2f(m_hatchlings[i]->getTransformedSize().x/2,
							m_hatchlings[i]->getTransformedSize().y/2),
			0));
	}

}
nest::~nest()
{
	std::cout<<"deleted nest"<<std::endl;
	//delete Animator;
}
void nest::update(float DeltaTime)
{
	for (int i = 0; i < 3; ++i)
	{
		m_animations[i]->update(DeltaTime);
	}
	//Animator->update(DeltaTime);
	//m_nestHitbox->Position = m_nestPosition;
}
void nest::draw(al::viewport* Viewport)
{
	window->draw(m_flamingonest);

	for (int i = 0; i < m_hatchlings.size(); ++i)
		Viewport->addSprite(m_hatchlings[i]);
}
#include "background.h"

background::background(sf::RenderWindow *Window)				
{
	window = Window;

	m_waterTexture = new sf::Texture();
	m_waterTexture->loadFromFile("Assets/ground_water_Background.png");
	m_waterTexture->setSmooth(true);
	m_water.setTexture(*m_waterTexture);
	m_water.setPosition(1280, 720);
	m_water.setOrigin(sf::Vector2f(1280, 462));

	m_skyTexture = new sf::Texture();
	m_skyTexture->loadFromFile("Assets/skyplaceholder.png");
	m_skyTexture->setSmooth(true);
	m_sky.setTexture(*m_skyTexture);
	m_sky.setPosition(0, 0);
	m_sky.setOrigin(sf::Vector2f(0, 0));

	m_groundTexture = new sf::Texture();
	m_groundTexture->loadFromFile("Assets/water_Opacity.png");
	m_groundTexture->setSmooth(true);
	m_ground.setTexture(*m_groundTexture);
	m_ground.setPosition(1280, 720);
	m_ground.setOrigin(sf::Vector2f(1036, 58));
}

background::~background()
{
	std::cout<<"deleted background"<<std::endl;
}

void background::update(float DeltaTime)
{
	//water.setPosition(100,100);
}

void background::draw()	
{
	window->draw(m_sky);
	window->draw(m_water);
	window->draw(m_ground);
	
}
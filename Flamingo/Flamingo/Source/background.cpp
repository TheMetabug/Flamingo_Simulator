#include "background.h"

using namespace al;

background::background(sf::RenderWindow *Window)				
{
	window = Window;

	m_waterTexture = new texture("ground_water_Background.png");
	m_water.setTexture(m_waterTexture);
	m_water.setPosition(vector(1280, 720));
	m_water.setOrigin(vector(1280, 462));

	m_skyTexture = new texture("skyplaceholder.png");
	m_sky.setTexture(m_skyTexture);
	m_sky.setPosition(vector(0, 0));
	m_sky.setOrigin(vector(0, 0));

	m_groundTexture = new texture("water_Opacity.png");
	m_ground.setTexture(m_groundTexture);
	m_ground.setPosition(vector(1280, 720));
	m_ground.setOrigin(vector(1036, 58));
}

background::~background()
{
	std::cout<<"deleted background"<<std::endl;
}

void background::update(float DeltaTime)
{
	//water.setPosition(100,100);
}

void background::draw(al::viewport* Viewport)	
{
	Viewport->draw(&m_sky);
	Viewport->draw(&m_water);
	Viewport->draw(&m_ground);
	
}
#include "background.h"

using namespace al;

background::background()				
{
	//window = Window;

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
	
}

void background::draw(al::viewport* Viewport)	
{
	Viewport->draw(&m_sky);
	Viewport->draw(&m_water);
	Viewport->draw(&m_ground);
	
}

//////////////////CLOUDS////////////////////////////

cloud::cloud()				
{
	//window = Window;

	m_cloudTexture_1 = new texture("cloud_one.png");
	m_cloud_1.setTexture(m_cloudTexture_1);
	m_cloud_1.setPosition(vector(1350, 100));
	m_cloud_1.setOrigin(vector(156, 69));

	m_cloudTexture_2 = new texture("cloud_two.png");
	m_cloud_2.setTexture(m_cloudTexture_2);
	m_cloud_2.setPosition(vector(500, 150));
	m_cloud_2.setOrigin(vector(156, 69));

	m_cloudTexture_3 = new texture("cloud_three.png");
	m_cloud_3.setTexture(m_cloudTexture_3);
	m_cloud_3.setPosition(vector(900, 200));
	m_cloud_3.setOrigin(vector(156, 69));



}

cloud::~cloud()
{
	std::cout<<"deleted cloud"<<std::endl;
}

void cloud::update(float DeltaTime)
{
	m_cloud_1.setPosition(m_cloud_1.getPosition() - vector(DeltaTime*8,0));
	if (m_cloud_1.getPosition().x <= -500)
		m_cloud_1.setPosition(vector(1500,100));

	m_cloud_2.setPosition(m_cloud_2.getPosition() - vector(DeltaTime*15,0));
	if (m_cloud_2.getPosition().x <= -500)
		m_cloud_2.setPosition(vector(1500,150));

	m_cloud_3.setPosition(m_cloud_3.getPosition() - vector(DeltaTime*4,0));
	if (m_cloud_3.getPosition().x <= -500)
		m_cloud_3.setPosition(vector(1500,200));

}

void cloud::draw(al::viewport* Viewport)	
{

	Viewport->draw(&m_cloud_1);
	Viewport->draw(&m_cloud_2);
	Viewport->draw(&m_cloud_3);
	
}
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
	m_startPosition_x = 1400;
	m_startPosition_y = 100;
	m_respawnPosition_x = 1400;
	m_respawnPosition_y = m_startPosition_y;

	m_cloudPositions.push_back(vector(m_startPosition_x , m_startPosition_y)); 
	m_cloudPositions.push_back(vector(m_startPosition_x - 600 , m_startPosition_y + 50));
	m_cloudPositions.push_back(vector(m_startPosition_x  - 1400, m_startPosition_y + 100));

	m_cloudsTexture.push_back(new texture("cloud_1.png"));
	m_cloudsTexture.push_back(new texture("cloud_2.png"));
	m_cloudsTexture.push_back(new texture("cloud_3.png"));

	for(int i = 0; i < 3; ++i)
	{
		m_clouds.push_back(new sprite(m_cloudsTexture[i]));
		m_clouds[i]->setPosition(m_cloudPositions[i]);
		m_clouds[i]->setOrigin(al::vector(m_clouds[i]->getSize().x/2,
							m_clouds[i]->getSize().y/2));
	}
}

cloud::~cloud()
{
	std::cout<<"deleted cloud"<<std::endl;
}

void cloud::update(float DeltaTime)
{
	for(int i = 0; i < 3; ++i)
	{
		m_clouds[i]->setPosition(m_clouds[i]->getPosition() - vector(DeltaTime*8*(i+0.5f),0));
		if(m_clouds[i]->getPosition().x <= -150)
			m_clouds[i]->setPosition(vector(m_respawnPosition_x, m_cloudPositions[i].y));
	}
}

void cloud::draw(al::viewport* Viewport)	
{
	for(int i = 0; i < 3; ++i)
	{
		Viewport->draw(m_clouds[i]);
	}	
}
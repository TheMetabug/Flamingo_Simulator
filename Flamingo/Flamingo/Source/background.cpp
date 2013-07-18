#include "background.h"

using namespace al;

background::background()				
{
	//window = Window;
	

	m_waterTexture = new texture("ground_water_Background.png");
	m_water.setTexture(m_waterTexture);
	m_water.setPosition(vector(1280, 720));
	m_water.setOrigin(vector(1280, 462));
	m_water.setLayer(1);

	m_skyTexture = new texture("skyplaceholder.png");
	m_sky.setTexture(m_skyTexture);
	m_sky.setPosition(vector(0, 0));
	m_sky.setOrigin(vector(0, 0));
	m_sky.setLayer(0);

	m_opacityTexture = new texture("water_Opacity.png");
	m_waterOpacity.setTexture(m_opacityTexture);
	m_waterOpacity.setPosition(vector(WINDOW_WIDTH, WINDOW_HEIGHT));
	m_waterOpacity.setOrigin(vector(m_waterOpacity.getTextureSize()));
	m_waterOpacity.setLayer(290);
	m_waterOpacity.setColor(255,255,255, 0.6f * 255);

		//cloud
	m_cloud = new cloud();

	// tree
	m_tree1 = new tree(vector(0.4,0.4),vector(315,420),1.0f);
	m_tree2 = new tree(vector(0.6,0.6),vector(1015,400),3.0f);



}

background::~background()
{
#if _DEBUG
	std::cout<<"deleted background"<<std::endl;
#endif
	delete m_skyTexture;
	delete m_waterTexture;
	delete m_opacityTexture;
	delete m_cloud;
	delete m_tree1;
	delete m_tree2;
}

void background::update(float DeltaTime)
{
	// cloud
	m_cloud->update(DeltaTime);

	// tree
	m_tree1->update(DeltaTime);
	m_tree2->update(DeltaTime);	
}

void background::draw(al::viewport* Viewport)
{
	Viewport->draw(&m_sky);
	Viewport->draw(&m_water);
	Viewport->draw(&m_waterOpacity);
			
	//cloud
	m_cloud->draw(Viewport);

	// tree
	m_tree1->draw(Viewport);
	m_tree2->draw(Viewport);

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
		m_clouds[i]->setColor(255,255,255,100);
	}
}

cloud::~cloud()
{
#if _DEBUG
	std::cout<<"deleted cloud"<<std::endl;
#endif

	for (int i = 0; i < m_clouds.size(); ++i)
		delete m_clouds[i];

	for (int i = 0; i < m_cloudsTexture.size(); ++i)
		delete m_cloudsTexture[i];
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

tree::tree(al::vector Scale, al::vector Position, float speed)
{
	m_treePosition = Position;
	m_treeScale = Scale;
	m_speed = speed;

	m_rotation = 0;
	m_timer = 0;
	//m_speed = speed;

	m_treeTexture = new texture("treeBackground.png");
	m_treeSprite = new sprite(m_treeTexture);
	m_treeSprite->setOrigin(vector(m_treeSprite->getSize().x/2,m_treeSprite->getSize().y));
	m_treeSprite->setPosition(m_treePosition);
	m_treeSprite->setScale(m_treeScale);
	m_treeSprite->setLayer(0);

}

tree::~tree()
{
	delete m_treeTexture;
}

void tree::update(float DeltaTime)
{
	m_timer += DeltaTime* m_speed;

	if(m_timer >= 0 && m_timer <= 4)
	m_rotation += DeltaTime*2;

	if(m_timer >=4)
	m_rotation -= DeltaTime*2;

	if(m_timer >= 8)
	{
		m_timer = 0;
		m_rotation = 0;
	}

	m_treeSprite->setRotation(m_rotation);
}

void tree::draw(al::viewport* Viewport)
{
	Viewport->draw(m_treeSprite);
}
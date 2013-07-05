#include "nest.h"

using namespace al;

nest::nest(collision* Collide)
{
	///// nest //////
	m_nestPosition = al::vector(200, 600);

	// create texture,sprite, positions etc
	m_nestTexture = new texture("NEST.png");
	m_flamingonest.setTexture(m_nestTexture);
	m_flamingonest.setPosition(m_nestPosition);
	m_flamingonest.setOrigin(vector(m_flamingonest.getSize().x/2,
		m_flamingonest.getSize().y/2));
	m_flamingonest.setScale(1,1);

	// hitbox
	m_nestHitbox = Collide->createHitBox(m_nestPosition,
		al::vector(m_flamingonest.getGlobalBounds().width,
					 m_flamingonest.getGlobalBounds().height/4), 
		al::vector(m_flamingonest.getGlobalBounds().width/2,
					 m_flamingonest.getGlobalBounds().height/2 - 170),
		0);

	///// hatchlings /////

	m_hatchlingRotation = 10;

	m_hatchlingPositions.push_back( al::vector(m_nestPosition.x, m_nestPosition.y - 60));
	m_hatchlingPositions.push_back( al::vector(m_nestPosition.x - 60, m_nestPosition.y - 30));
	m_hatchlingPositions.push_back( al::vector(m_nestPosition.x + 60, m_nestPosition.y - 30));

	m_hatchlingTexture = new texture("Hatchling_sheet_v2.png");

	for (int i = 0; i < 3; ++i)
	{
		// create texture,sprite, positions etc
		m_hatchlings.push_back(new sprite(m_hatchlingTexture));
		m_animations.push_back(new animation(m_hatchlings[i], 3, 256, 256, false, 0));
		m_hatchlings[i]->setPosition(m_hatchlingPositions[i]);
		m_hatchlings[i]->setOrigin(al::vector(m_hatchlings[i]->getSize().x/2,
							   m_hatchlings[i]->getSize().y/2));
		m_hatchlings[i]->setScale(0.5f,0.5f);

		//animation

		//hitbox
		m_hatchlingHitboxes.push_back( Collide->createHitBox(m_hatchlingPositions[i],
			al::vector(m_hatchlings[i]->getTransformedSize().x,
							m_hatchlings[i]->getTransformedSize().y), 
			al::vector(m_hatchlings[i]->getTransformedSize().x/2,
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
	m_hatchlingRotation += DeltaTime/2;

	for (int i = 0; i < 3; ++i)
	{
		m_animations[i]->update(DeltaTime);
		m_hatchlings[i]->setRotation(15 * sin(m_hatchlingRotation*10));
	}


	//Animator->update(DeltaTime);
	//m_nestHitbox->Position = m_nestPosition;
}
void nest::draw(al::viewport* Viewport)
{
	Viewport->draw(&m_flamingonest);

	for (int i = 0; i < m_hatchlings.size(); ++i)
		Viewport->draw(m_hatchlings[i]);
}

void nest::egg(float DeltaTime)	
{

}

void nest::sleep(float DeltaTime)
{

}

bool nest::eat(float DeltaTime, int Id, float foodValue)	
{
	if (Id != 0)
	{
		if(foodValue > 0)
		{
			m_animations[Id-1]->ChangeAnimation(9,1,9,5);
		}
		else
		{
			m_animations[Id-1]->ChangeAnimation(3,1,3,5);
		}
	}
	return false;
}

void nest::die(float DeltaTime)	
{

}

void nest::fly(float DeltaTime)	
{

}

void nest::mad(float DeltaTime)
{
	for(int i = 0; i < m_hatchlings.size(); ++i)
	m_animations[i]->ChangeAnimation(12,1,12,5);
}
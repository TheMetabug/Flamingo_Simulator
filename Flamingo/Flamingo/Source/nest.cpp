#include "nest.h"

using namespace al;

nest::nest(collision* Collide, gui* Gui)
{
	///// nest //////
	m_nestPosition = vector(120, 550);
	m_eggPosition = m_nestPosition + vector(0,60);
	m_eggVector = vector(-80,-30);

	// score //
	m_gui = Gui;

	// create texture,sprite, positions etc
	m_nestTexture = new texture("NEST.png");
	m_flamingonest.setTexture(m_nestTexture);
	m_flamingonest.setPosition(m_nestPosition);
	m_flamingonest.setOrigin(vector(m_flamingonest.getSize().x/2,
									m_flamingonest.getSize().y/2));
	m_flamingonest.setScale(1,1);
	m_flamingonest.setLayer(291);
	// hitbox
	m_nestHitbox = Collide->createHitBox(m_nestPosition,
		al::vector(m_flamingonest.getGlobalBounds().width,
					 m_flamingonest.getGlobalBounds().height/4), 
		al::vector(m_flamingonest.getGlobalBounds().width/2,
					 m_flamingonest.getGlobalBounds().height/2 - 170),
		0);

	/// egg ///
	m_eggTexture = new texture("hatchingAnimation.png");

	for (int i = 0; i < 5; ++i)
	{
		addEgg();
	}


	///// hatchlings /////

	for (int i = 0; i < 3; ++i)
	{
		m_hatchlings.push_back(new hatchling());
	}

	m_hatchlingRotation = 10;

	m_hatchlings[0]->m_position = vector(m_nestPosition.x - 60, m_nestPosition.y - 40);
	m_hatchlings[1]->m_position = vector(m_nestPosition.x + 10, m_nestPosition.y);
	m_hatchlings[2]->m_position = vector(m_nestPosition.x + 80, m_nestPosition.y + 40);

	m_hatchlingTexture = new texture("Hatchling_sheet_v2.png");

	

	for (int i = 0; i < m_hatchlings.size(); ++i)
	{
		// create texture,sprite, positions etc
		m_hatchlings[i]->m_sprite = new sprite(m_hatchlingTexture);
		m_hatchlings[i]->m_animation = new animation(m_hatchlings[i]->m_sprite, 3, 256, 256, false, 0);
		//m_hatchlings.push_back(new sprite(m_hatchlingTexture));
		//m_animations.push_back(new animation(m_hatchlings[i], 3, 256, 256, false, 0));
		m_hatchlings[i]->m_sprite->setPosition(m_hatchlings[i]->m_position);
		m_hatchlings[i]->m_sprite->setOrigin(al::vector(	m_hatchlings[i]->m_sprite->getSize().x/2,
														m_hatchlings[i]->m_sprite->getSize().y/2));
		m_hatchlings[i]->m_sprite->setScale(0.5f,0.5f);
		m_hatchlings[i]->m_sprite->setLayer(294);

		//animation

		//hitbox
		m_hatchlings[i]->m_hitbox = Collide->createHitBox(m_hatchlings[i]->m_position,
			al::vector(	m_hatchlings[i]->m_sprite->getTransformedSize().x,
						m_hatchlings[i]->m_sprite->getTransformedSize().y), 
						al::vector(	m_hatchlings[i]->m_sprite->getTransformedSize().x/2,
									m_hatchlings[i]->m_sprite->getTransformedSize().y/2),
						0);
	}

}
nest::~nest()
{
	std::cout<<"deleted nest"<<std::endl;
	//delete Animator;
}
void nest::update(float DeltaTime)
{
	//m_timer += DeltaTime;

	m_hatchlingRotation += DeltaTime/2;

	for (int i = 0; i < 3; ++i)
	{
		m_hatchlings[i]->m_timer += DeltaTime;
		m_hatchlings[i]->m_animation->update(DeltaTime);
		m_hatchlings[i]->m_sprite->setRotation(15 * sin(m_hatchlingRotation*10));

		if(m_hatchlings[i]->m_timer > 1.5f)
		{
			m_hatchlings[i]->m_animation->ChangeAnimation(0,1,0,5);
			m_hatchlings[i]->m_timer = 0;
		}
	}

}
void nest::draw(al::viewport* Viewport)
{
	Viewport->draw(&m_flamingonest);

	for (int i = m_eggs.size()-1; i >= 0; --i)
		Viewport->draw(m_eggs[i]);

	for (int i = 0; i < m_hatchlings.size(); ++i)
	{
		if (m_hatchlings[i]->m_isThere)
			Viewport->draw(m_hatchlings[i]->m_sprite);
	}

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
			m_hatchlings[Id-1]->m_animation->ChangeAnimation(9,1,9,5);
 			m_gui->SCORE += 100;

		}
		else
		{
			m_hatchlings[Id-1]->m_animation->ChangeAnimation(3,1,3,5);
			m_gui->SCORE -= 50;
		}
		m_hatchlings[Id-1]->m_timer = 0;
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
	{
		m_hatchlings[i]->m_animation->ChangeAnimation(12,1,12,5);
		m_hatchlings[i]->m_timer = 0;
	}
}

void nest::happy(float DeltaTime)
{
	for(int i = 0; i < m_hatchlings.size(); ++i)
	{
		m_hatchlings[i]->m_animation->ChangeAnimation(9,1,9,5);
		m_hatchlings[i]->m_timer = 0;
	}
}

void nest::addEgg()
{
	float width = 256, height = 256;
	m_eggs.push_back(new sprite(m_eggTexture));
	m_eggs.back()->setTextureRectangle(rectangle(vector(),width,height));
	m_eggs.back()->setOrigin(vector(width/2, height/2));
	m_eggs.back()->setScale(0.2f);
	m_eggs.back()->setLayer(294);

	for (int i = 0; i < m_eggs.size(); ++i)
	{
		m_eggs[i]->setPosition(
			m_eggPosition +
			(m_eggVector / m_eggs.size()) * (i + 1)
			);
	}

}
#include "nest.h"

using namespace al;

hatchling::hatchling(texture* HatchlingTexture, al::texture* FlyTexture, collision* Collide)
	: m_isThere(true),
		m_fly(false),
		m_timer(0),
		m_rotation(10),
		m_state(0),
		m_flyScale(2.0f/3.0f)
{
		m_sprite = new sprite(HatchlingTexture);
		m_animation = new animation(m_sprite, 2, 254, 254, false, 0);
		//m_hatchlings.push_back(new sprite(m_hatchlingTexture));
		//m_animations.push_back(new animation(m_hatchlings[i], 3, 256, 256, false, 0));
		m_sprite->setPosition(m_position);
		m_sprite->setOrigin(al::vector(	m_sprite->getSize().x/2, m_sprite->getSize().y/2));
		m_sprite->setScale(0.5f,0.5f);
		m_sprite->setLayer(3);

		//animation
		m_eatPoints = 0;

		//hitbox
		m_hitbox = Collide->createHitBox(m_position,
			al::vector(	m_sprite->getTransformedSize().x,
						m_sprite->getTransformedSize().y), 
						al::vector(	m_sprite->getTransformedSize().x/2,
									m_sprite->getTransformedSize().y/2),
						0);

		
	m_flySprite = new sprite(FlyTexture);
	m_flyAnimation = new animation(m_flySprite, 1, 256, 472, 7.0f,0);
	m_flySprite->setScale(m_flyScale);
	m_flySprite->setLayer(2);
	m_flySprite->setOrigin(vector(m_flySprite->getSize().x/2, 430));

}


hatchling::~hatchling()
{
	delete m_sprite;
	delete m_animation;
}

void hatchling::update(float DeltaTime)
{
	m_rotation += DeltaTime/2;

	m_timer += DeltaTime;

	switch (m_state)
	{
	case 0:
		m_animation->update(DeltaTime);
		m_sprite->setRotation(15 * sin(m_rotation*10));

		if(m_timer > 1.5f)
		{
			m_animation->ChangeAnimation(0,1,0,5);
			m_timer = 0;
		}

		m_sprite->setPosition(m_position);
		m_hitbox->Position = m_position;
		break;
	case 1:
		m_flyAnimation->update(DeltaTime);
		if (m_flyAnimation->getCurrentFrame() == 4)
		{
			m_state = 2;
			m_timer = -1;
		}
		break;
	case 2:
		{
			vector finalPosition = vector(500,500);
			float travelTime = 2.0f;
			if (m_timer > 0.0f)
			{
				//m_position.y -= 250 * DeltaTime;
				m_flySprite->setPosition(m_position + (m_timer / travelTime) *(finalPosition - m_position));
			}
			if (m_timer > travelTime)
			{
				m_flySprite->setPosition(finalPosition);
				m_state = 3;
				m_timer = -5;
			}
		}
		break;
	case 3:
		if (m_timer < 0)
		{
			m_flySprite->setScale(m_flyScale * ((m_timer / -5.0f)));
		}
		else
		{
			m_flyAnimation->ChangeAnimation(0,1,0,1);
			m_flySprite->setScale(m_flyScale);
			m_state = 0;
			m_hitbox->isEnabled = true;
			m_eatPoints = 0;
			m_isThere = true;
			m_timer = 0;
		}
		break;
	}
}

void hatchling::draw(viewport* Viewport)
{
	switch (m_state)
	{
	case 0:
		if (m_isThere)
			Viewport->draw(m_sprite);
		break;
	case 1:
		if (m_isThere)
			Viewport->draw(m_sprite);
		Viewport->draw(m_flySprite);
		break;
	case 2:
		Viewport->draw(m_flySprite);
		break;
	case 3:
		Viewport->draw(m_flySprite);
		break;
	default:
		std::cout<<"damn noob you forgot something"<<std::endl;
		break;

	}
}






nest::nest(collision* Collide, gui* Gui)
{
	///// nest //////
	m_nestPosition = vector(95, 535);
	m_eggPosition = m_nestPosition + vector(0,60);
	m_eggVector = vector(-80,-30);

	// score //
	m_gui = Gui;

	// create texture,sprite, positions etc
	m_nestTexture = new texture("flamingo_nestPieces.png");
	m_flamingonest.setTexture(m_nestTexture);
	m_flamingonest.setTextureRectangle(rectangle(vector(),m_flamingonest.getTextureSize().x/2,
										m_flamingonest.getTextureSize().y));
	m_flamingonest.setPosition(m_nestPosition);
	m_flamingonest.setOrigin(vector(m_flamingonest.getSize().x/2,
									m_flamingonest.getSize().y/2));
	m_flamingonest.setScale(1,1);
	m_flamingonest.setLayer(2);


	m_flamingonestFront.setTexture(m_nestTexture);
	m_flamingonestFront.setTextureRectangle(rectangle(vector(m_flamingonest.getTextureSize().x/2,0),416,
										m_flamingonest.getTextureSize().y));
	m_flamingonestFront.setPosition(m_nestPosition);
	m_flamingonestFront.setOrigin(vector(m_flamingonest.getSize().x/2,
									m_flamingonest.getSize().y/2));
	m_flamingonestFront.setScale(1,1);
	m_flamingonestFront.setLayer(3);




	// hitbox
	m_nestHitbox = Collide->createHitBox(m_nestPosition,
		al::vector(m_flamingonest.getGlobalBounds().width,
					 m_flamingonest.getGlobalBounds().height/4), 
		al::vector(m_flamingonest.getGlobalBounds().width/2,
					 m_flamingonest.getGlobalBounds().height/2 - 170),
		0);
	m_nestHitbox->isRound = false;

	/// egg ///
	m_eggTexture = new texture("hatchingAnimation.png");

	for (int i = 0; i < 5; ++i)
	{
		addEgg();
	}

	// the egg ///
	m_theEgg = new sprite(m_eggTexture);
	m_eggAnimation = new animation(m_theEgg, 6, 256, 256);
	m_theEgg->setLayer(3);
	m_theEgg->setPosition(m_eggPosition);
	vector asdf = vector(m_theEgg->getSize()/2);
	m_theEgg->setOrigin(vector(m_theEgg->getSize()/2));
	m_theEgg->setScale(0.2f);

	///// hatchlings /////

	m_hatchlingTexture = new texture("Hatchling_sheet.png");
	m_hatchlingFlyTexture = new texture("flamingoGrowupAnimation.png");

	for (int i = 0; i < 3; ++i)
	{
		m_hatchlings.push_back(new hatchling(m_hatchlingTexture, m_hatchlingFlyTexture, Collide));
	}


	m_hatchlings[0]->m_position = vector(m_nestPosition.x - 60, m_nestPosition.y - 40);
	m_hatchlings[1]->m_position = vector(m_nestPosition.x + 10, m_nestPosition.y);
	m_hatchlings[2]->m_position = vector(m_nestPosition.x + 80, m_nestPosition.y + 40);




	// hatchling fly sprite


}
nest::~nest()
{
	std::cout<<"deleted nest"<<std::endl;
	delete m_eggTexture;
	delete m_hatchlingTexture;
	delete m_nestTexture;
	delete m_theEgg;
	delete m_eggAnimation;
	for (int i = 0; i < m_eggs.size(); ++i)
		delete m_eggs[i];

}

void nest::update(float DeltaTime)
{
	//m_timer += DeltaTime;



	for (int i = 0; i < 3; ++i)
	{
		m_hatchlings[i]->update(DeltaTime);
	}

}
void nest::draw(al::viewport* Viewport)
{
	Viewport->draw(&m_flamingonest);

	//Viewport->draw(m_hatchlingFly);

	for (int i = 0; i < m_hatchlings.size(); ++i)
	{
		m_hatchlings[i]->draw(Viewport);
	}

	for (int i = m_eggs.size()-1; i >= 0; --i)
		Viewport->draw(m_eggs[i]);

	Viewport->draw(m_theEgg);
	
	Viewport->draw(&m_flamingonestFront);
	

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
 			m_gui->SCORE += 100;
			m_hatchlings[Id-1]->m_animation->ChangeAnimation(6,2,6,5);
			m_hatchlings[Id-1]->m_timer = 0;
			m_hatchlings[Id-1]->m_eatPoints += foodValue;
			if(m_hatchlings[Id-1]->m_eatPoints >= 3)
			{
				fly(DeltaTime,Id-1);

				m_hatchlings[Id-1]->m_flySprite->setPosition(m_hatchlings[Id-1]->m_position);
				m_hatchlings[Id-1]->m_isThere = false;
				m_hatchlings[Id-1]->m_hitbox->isEnabled = false;
				m_hatchlings[Id-1]->m_flyAnimation->ChangeAnimation(0,5,0,5);
				m_hatchlings[Id-1]->m_state = 1;
			}

		}
		else
		{
			m_gui->SCORE -= 50;
			m_hatchlings[Id-1]->m_animation->ChangeAnimation(2,1,2,5);
			m_hatchlings[Id-1]->m_timer = 0;
			m_hatchlings[Id-1]->m_eatPoints += foodValue;
			
			return false;
		}

	}
	else
		return false;
	return true;
}

void nest::die(float DeltaTime)	
{

}

void nest::fly(float DeltaTime, int Id)	
{
	//if(m_hatchlingFlyAnimation->getCurrentFrame() == 4)
	//{
	//	m_hatchlingFlyAnimation->ChangeAnimation(5,1,5,5);
	//	//m_hatchlingFly->setPosition(
	//}
	

}

void nest::mad(float DeltaTime)
{
	for(int i = 0; i < m_hatchlings.size(); ++i)
	{
		m_hatchlings[i]->m_animation->ChangeAnimation(8,1,8,5);
		m_hatchlings[i]->m_timer = 0;
	}
}

void nest::happy(float DeltaTime)
{
	for(int i = 0; i < m_hatchlings.size(); ++i)
	{
		m_hatchlings[i]->m_animation->ChangeAnimation(6,1,6,5);
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
	m_eggs.back()->setLayer(3);

	for (int i = 0; i < m_eggs.size(); ++i)
	{
		vector asdf = m_eggPosition + (m_eggVector / m_eggs.size()) * (i + 1);
		m_eggs[i]->setPosition(
			m_eggPosition +
			(m_eggVector / m_eggs.size()) * (i + 1)
			);
		m_eggCount++;
	}

}
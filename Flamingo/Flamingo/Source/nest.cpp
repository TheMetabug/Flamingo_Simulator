#include "nest.h"

using namespace al;

//Hatchling

hatchling::hatchling(nest* Nest, collision* Collide)
	:	m_flyScale(2.0f/3.0f)
{
	m_sprite = new sprite(Nest->m_hatchlingTexture);
		m_animation = new animation(m_sprite, 2, 254, 254, false, 0);
		m_particleEngine = Nest->m_particleEngine;

		m_sprite->setPosition(m_position);
		m_sprite->setOrigin(al::vector(	m_sprite->getSize().x/2, m_sprite->getSize().y/2));
		m_sprite->setScale(0.5f,0.5f);
		m_sprite->setLayer(3);


		//hitbox
		m_hitbox = Collide->createHitBox(m_position,
			al::vector(	m_sprite->getTransformedSize().x,
						m_sprite->getTransformedSize().y), 
						al::vector(	m_sprite->getTransformedSize().x/2,
									m_sprite->getTransformedSize().y/2),
						0);

		
		m_flySprite = new sprite(Nest->m_hatchlingFlyTexture);
	m_flyAnimation = new animation(m_flySprite, 1, 256, 472, 7.0f,0);
	m_flySprite->setScale(m_flyScale);
	m_flySprite->setLayer(2);
	m_flySprite->setOrigin(vector(m_flySprite->getSize().x/2, 430));

	m_travelTime = 0;

	m_nest = Nest;

	reset();
}
hatchling::~hatchling()
{
	delete m_sprite;
	delete m_animation;
	delete m_flySprite;
	delete m_flyAnimation;
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
			vector finalPosition = vector(280,100);
			m_travelTime = 2.0f;
			if (m_timer > 0.0f)
			{
				//m_position.y -= 250 * DeltaTime;
				m_flySprite->setPosition(m_position + (m_timer / m_travelTime) *(finalPosition - m_position));
				m_flySprite->setScale(m_flyScale * ((2.0f - m_timer) / 2.0f ) );
			}
			if (m_timer > m_travelTime)
			{
				m_flySprite->setPosition(finalPosition);
				m_state = 3;
				m_timer = -2;
				m_nest->m_soundLibrary->m_sounds[29]->play(); //point
			}
		}
		break;
	case 3:
		if (m_timer > 0)
		{
			m_flyAnimation->ChangeAnimation(0,1,0,1);
			m_flySprite->setScale(m_flyScale);
			m_state = 0;
			m_eatPoints = 0;
			m_fly = false;
			
			m_timer = 0;
		}
		break;
	case 4:
		if (m_timer > 0)
		{
			m_state = 0;
			m_timer = 0;
			m_nest->m_soundLibrary->m_sounds[7]->play(); //failure
			m_fly = false;
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
	case 4:
		break;
	default:
		std::cout<<"damn noob you forgot something"<<std::endl;
		break;

	}
}

void hatchling::fly()
{
	if (m_state == 0)
	{
		m_flySprite->setPosition(m_position);
		m_isThere = false;
		m_fly = true;
		m_hitbox->isEnabled = false;
		m_flyAnimation->ChangeAnimation(0,5,0,5);
		m_state = 1;
		m_animation->ChangeAnimation(0,1);
	}
}
void hatchling::eat(float foodValue)
{
	if (m_state == 0)
	{
		if (foodValue > 0)
		{
			m_animation->ChangeAnimation(6,2);
			m_timer = 0;
			m_eatPoints += foodValue;
		}
		else
		{
			die();
			//m_animation->ChangeAnimation(2,1);
			m_timer = 0;
			//m_eatPoints += foodValue;
		}
	}
}
void hatchling::mad()
{
	if (m_state == 0)
	{
		m_animation->ChangeAnimation(8,1);
		m_timer = 0;
	}
}
void hatchling::happy()
{
	if (m_state == 0)
	{
		m_animation->ChangeAnimation(6,1);
		m_timer = 0;
	}
}
void hatchling::die()
{
	m_isThere = false;
	m_fly = true;
	m_hitbox->isEnabled = false;
	m_state = 4;
	m_timer = -5;
	for (int i = 0; i < 100; ++i)
	{
		m_particleEngine->addSplash(m_position,vector());
	}
}

void hatchling::reset()
{
	m_isThere = true;
	m_hitbox->isEnabled = true;
	m_fly = false;
	m_timer = 0;
	m_rotation = 10;
	m_state = 0;
	m_eatPoints = 0;

	m_animation->ChangeAnimation(0,1);
}

//Nest

nest::nest(collision* Collide, gui* Gui, particleEngine* ParticleEngine)
{
	///// nest //////
	m_nestPosition = vector(95, 535);
	m_eggPosition = m_nestPosition + vector(0,60);
	m_eggVector = vector(-80,-30);

	m_particleEngine = ParticleEngine;

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


	m_travelTime = 2.0f;

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


	// the egg ///
	m_theEgg = new sprite(m_eggTexture);
	m_eggAnimation = new animation(m_theEgg, 6, 256, 256);
	m_theEgg->setLayer(3);
	m_theEgg->setPosition(m_eggPosition);
	m_theEgg->setOrigin(vector(m_theEgg->getSize()/2));
	m_theEgg->setScale(0.2f);

	///// hatchlings /////

	m_hatchlingTexture = new texture("Hatchling_sheet.png");
	m_hatchlingFlyTexture = new texture("flamingoGrowupAnimation.png");

	for (int i = 0; i < 3; ++i)
	{
		m_hatchlings.push_back(new hatchling(this, Collide));
	}


	m_hatchlings[0]->m_position = vector(m_nestPosition.x - 60, m_nestPosition.y - 40);
	m_hatchlings[1]->m_position = vector(m_nestPosition.x + 10, m_nestPosition.y);
	m_hatchlings[2]->m_position = vector(m_nestPosition.x + 80, m_nestPosition.y + 40);


	reset();


	//sound
	m_soundLibrary = new soundLibrary();

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

	m_eggAnimation->update(DeltaTime);

	for (int i = 0; i < 3; ++i)
	{
		m_hatchlings[i]->update(DeltaTime);

		if (!m_hatchlings[i]->m_isThere && !m_hatchlings[i]->m_fly && !m_hatching && !m_egging && m_eggCount > 0)
		{
			m_whichBird = i;
			m_egging = true;
			m_eggTimer = 0;
			m_eggTarget = m_hatchlings[i]->m_position;
		}
	}

	if (m_egging || m_hatching)
	{
		egg(DeltaTime);
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
	m_eggTimer += DeltaTime;

	if (m_eggTimer < m_travelTime)
	{
		m_theEgg->setPosition(m_eggPosition +
			(m_eggTarget - m_eggPosition) * ((m_eggTimer)/m_travelTime));
	}
	else
	{
		if (m_egging)
		{
			m_theEgg->setPosition(m_eggTarget);
			m_eggAnimation->ChangeAnimation(0,7);
			m_egging = false;
			m_hatching = true;
			m_soundLibrary->m_sounds[13]->play(); //kuoriutuminen
		}
		if (m_eggAnimation->getCurrentFrame() == 6)
		{
			m_theEgg->setPosition(m_eggPosition);

			removeEgg();
			m_soundLibrary->m_sounds[14]->play(); //kuoriutuminen kaksi

			if (m_eggCount > 0)
				m_eggAnimation->ChangeAnimation(0,1);
			else
				m_eggAnimation->ChangeAnimation(6,1);
			m_hatching = false;
			m_hatchlings[m_whichBird]->reset();
		}
	}
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
			if(m_hatchlings[Id-1]->m_eatPoints >= 1) // change 1 to 3!!!!!!!!!! 1 is just for debugging
			{
 				m_gui->SCORE += 500;
				m_hatchlings[Id-1]->fly();
			}
			else
			{
 				m_gui->SCORE += 100;
				m_hatchlings[Id-1]->eat(foodValue);
			}

		}
		else
		{
			m_gui->SCORE -= 50;
			m_hatchlings[Id-1]->eat(foodValue);
			
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
		m_hatchlings[i]->mad();
	}
}
void nest::happy(float DeltaTime)
{
	for(int i = 0; i < m_hatchlings.size(); ++i)
	{
		m_hatchlings[i]->happy();
	}
}

void nest::addEgg()
{
	m_eggCount++;
	float width = 256, height = 256;
	m_eggs.push_back(new sprite(m_eggTexture));
	m_eggs.back()->setTextureRectangle(rectangle(vector(),width,height));
	m_eggs.back()->setOrigin(vector(width/2, height/2));
	m_eggs.back()->setScale(0.2f);
	m_eggs.back()->setLayer(3);

	updateEggPositions();
}
void nest::removeEgg()
{
	m_eggCount--;
	if (m_eggs.size()>0)
		m_eggs.pop_back();

	updateEggPositions();
}
void nest::updateEggPositions()
{
	for (int i = 0; i < m_eggs.size(); ++i)
	{
		m_eggs[i]->setPosition(
			m_eggPosition +
			(m_eggVector / m_eggs.size()) * (i + 1)
			);
	}
}
void nest::reset()
{
	m_eggCount = 1;
	for (int i = m_eggs.size()-1; i >= 0; --i)
	{
		delete m_eggs[i];
	}

	m_eggs.clear();

	for (int i = 0; i < 5; ++i)
	{
		addEgg();
	}
	
	for (int i = 0; i < m_hatchlings.size(); ++i)
	{
		m_hatchlings[i]->reset();
	}

	m_hatching = false;
	m_egging = false;
	m_noEggs = false;
	m_theEgg->setPosition(m_eggPosition);
	m_eggAnimation->ChangeAnimation(0,1);
}
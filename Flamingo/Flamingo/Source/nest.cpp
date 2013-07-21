#include "nest.h"

using namespace al;

//Hatchling

thought::thought(texture* ThoughtBubble, pups::pickup* Pickup, float Rotation)
{
	m_sprite.setTexture(ThoughtBubble);
	m_sprite.setLayer(9);
	m_sprite.setOrigin(vector(m_sprite.getSize().x/2,m_sprite.getSize().y*3/2));
	m_sprite.setColor(255,255,255,0);
	m_sprite.setRotation(Rotation-270);
	
	vector offset(0,m_sprite.getSize().y);
	offset.rotate(Rotation-270);
	m_pickupSprite.setTexture(Pickup->m_texture);
	m_pickupSprite.setTextureRectangle(rectangle(vector(0,256*Pickup->m_itemName),vector(256,256)));
	m_pickupSprite.setLayer(10);
	m_pickupSprite.setOrigin(m_sprite.getSize()/2 + offset);
	m_pickupSprite.setColor(255,255,255,0);

	m_timer = 0;
}
void thought::update(float DeltaTime, vector Position)
{
	m_timer += DeltaTime;

	if (m_timer < 3)
	{
		m_sprite.setColor(255,255,255,m_timer * 50);
		m_pickupSprite.setColor(255,255,255,m_timer * 50);
	}
	else
	{
		m_sprite.setColor(255,255,255,150);
		m_pickupSprite.setColor(255,255,255,150);
	}

	m_sprite.setPosition(Position);
	m_pickupSprite.setPosition(Position);
}
void thought::draw(viewport* Viewport)
{
	Viewport->draw(&m_sprite);
	Viewport->draw(&m_pickupSprite);
}
void thought::loseThought()
{}


hatchling::hatchling(nest* Nest, collision* Collide)
	:	m_flyScale(2.0f/3.0f)
{
	m_sprite = new sprite(Nest->m_hatchlingTexture);
	m_animation = new animation(m_sprite, 2, 254, 254, false, 0);
	m_particleEngine = Nest->m_particleEngine;

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


	desire();

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
	case 0: // Hatchling just chilling
		
		if (m_desiredItem > pups::ItemName::ItemsCount)
		{
			m_desireTimer += DeltaTime;
			if (m_desireTimer > 0)
			{
				desire();
			}
		}

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
	case 1: // Hatchling growing
		m_flyAnimation->update(DeltaTime);
		if (m_flyAnimation->getCurrentFrame() == 4)
		{
			m_state = 2;
			m_timer = -1;
			m_flySprite->setLayer(10);
		}
		break;
	case 2: // Hathling flying away
		{
			vector finalPosition = vector(140,700);
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
				m_timer = -2; // Viive
				m_nest->m_soundLibrary->m_sounds[29]->play(); //point
				m_nest->m_gui->addScore(finalPosition,500);
				m_nest->m_flamCount += 1;
			}
		}
		break;
	case 3: // Hatchling flown
		if (m_timer > 0)
		{
			m_flyAnimation->ChangeAnimation(0,1);
			m_flySprite->setScale(m_flyScale);
			m_state = 0;
			m_eatPoints = 0;
			m_fly = false;
			m_nest->m_hatchCount--;
			
			m_timer = 0;
		}
		break;
	case 4: // Hathcling killed
		if (m_timer > 0)
		{
			m_state = 0;
			m_timer = 0;
			//m_nest->m_soundLibrary->m_sounds[7]->play(); //failure
			m_fly = false;
			m_nest->m_hatchCount--;
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
#if _DEBUG
		std::cout<<"damn noob you forgot something"<<std::endl;
#endif
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
void hatchling::eat(pups::pickup* pickup)
{
	if (m_state == 0)
	{

		if (pickup->m_foodValue > 0)
		{
			m_animation->ChangeAnimation(6,2);
			m_timer = 0;
			m_eatPoints += pickup->m_foodValue;
		}
		else
		{
			die();
			//m_animation->ChangeAnimation(2,1);
			//m_timer = 0;
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
	m_nest->shocked();
	for (int i = 0; i < 100; ++i)
	{
		m_particleEngine->addFeather(m_position);
	}
}
void hatchling::desire()
{
	m_desireTimer = -( (rand()%100)/100.0f * 4 + 2);
	m_desiredItem = pups::ItemName(rand()%pups::ItemName::Shoe); //randoms one of the edible
}

void hatchling::shocked()
{
	if (m_state == 0)
	{
		m_animation->ChangeAnimation(4,1);
		m_timer = 0;
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

	m_thoughtBubble = new texture("thoughtBubble.png");

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
	m_flamingonestFront.setLayer(7);


	m_travelTime = 2.0f;

	m_theEggScale = 0.2f;
	m_scale = m_theEggScale;

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
	m_theEgg->setOrigin(vector(m_theEgg->getSize().x/2,m_theEgg->getSize().x/2));
	m_theEgg->setScale(0.2f);

	///// hatchlings /////

	m_hatchlingTexture = new texture("Hatchling_sheet.png");
	m_hatchlingFlyTexture = new texture("flamingoGrowupAnimation.png");

	for (int i = 0; i < 3; ++i)
	{
		m_hatchlings.push_back(new hatchling(this, Collide));
		m_hatchlings.back()->m_sprite->setLayer(4 + i);
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
#if _DEBUG
	std::cout<<"deleted nest"<<std::endl;
#endif
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
	m_eggCount = m_eggs.size();
	if (!(m_egging || m_hatching) && m_eggAnimation->getCurrentFrame() != 7)
		m_eggCount++;
	m_gui->m_eggCount = m_eggCount;
	m_gui->m_flamCount = m_flamCount;
	m_eggAnimation->update(DeltaTime);

	for (int i = 0; i < 3; ++i)
	{
		m_hatchlings[i]->update(DeltaTime);

		if (!m_hatchlings[i]->m_isThere && !m_hatchlings[i]->m_fly && !m_hatching && !m_egging && m_eggCount > 0)
		{
			m_whichBird = i;
			m_theEgg->setLayer(3 + i);
			m_egging = true;
			m_eggTimer = 0;
			m_eggTarget = vector(m_hatchlings[i]->m_position.x + 5.0f,m_hatchlings[i]->m_position.y + 10.0f);
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
		m_theEgg->setScale(m_scale += DeltaTime/6);
	}
	else
	{
		if (m_egging)
		{
			m_theEgg->setPosition(m_eggTarget);
			m_eggAnimation->ChangeAnimation(0,7);
			m_egging = false;
			m_hatching = true;
			m_soundLibrary->m_sounds[13]->playWithRandPitch(0.2f); //kuoriutuminen
		}
		if (m_eggAnimation->getCurrentFrame() == 6)
		{
			m_theEgg->setPosition(m_eggPosition);
			m_theEgg->setLayer(6);
			
			m_scale = m_theEggScale;
			m_theEgg->setScale(m_scale);
			m_hatchCount++;

			
			m_soundLibrary->m_sounds[14]->playWithRandPitch(0.2f); //kuoriutuminen kaksi

			if (m_eggs.size() > 0) // remove egg from vector
			{
				m_eggAnimation->ChangeAnimation(0,1);
				removeEgg();
			}
			else // remove the egg
				m_eggAnimation->ChangeAnimation(7,1);

			m_hatching = false;
			m_hatchlings[m_whichBird]->reset();
			m_hatchlings[m_whichBird]->m_sprite->setLayer(4 + m_whichBird);
			
		}
	}
}
void nest::sleep(float DeltaTime)
{

}

bool nest::eat(float DeltaTime, int Id, pups::pickup* pickup)	
{
	if (Id != 0)
	{
		if(pickup->m_foodValue > 0)
		{
			m_hatchlings[Id-1]->eat(pickup);

			if(m_hatchlings[Id-1]->m_eatPoints >= 2) // change 1 to 3!!!!!!!!!! 1 is just for debugging
			{
				m_hatchlings[Id-1]->fly();
			}
			else
			{
				m_gui->addScore(m_hatchlings[Id-1]->m_position,100);
			}

		}
		else
		{
			m_gui->addScore(m_hatchlings[Id-1]->m_position,-50);
			m_hatchlings[Id-1]->eat(pickup);
			
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
void nest::mad()
{
	for(int i = 0; i < m_hatchlings.size(); ++i)
	{
		m_hatchlings[i]->mad();
	}
}
void nest::happy()
{
	for(int i = 0; i < m_hatchlings.size(); ++i)
	{
		m_hatchlings[i]->happy();
	}
}
void nest::shocked()
{
	for(int i = 0; i < m_hatchlings.size(); ++i)
	{
		m_hatchlings[i]->shocked();
	}
}
bool nest::enemyTakingEgg()
{
	if (m_eggCount > 1)
	{
		removeEgg();
		return true;
	}
	else if (m_eggCount == 1)
	{
		m_eggAnimation->ChangeAnimation(6,1);
		return true;
	}
	return false;
}

void nest::addEgg()
{

	if (m_eggAnimation->getCurrentFrame() != 7)
	{
		float width = 256, height = 256;
		m_eggs.push_back(new sprite(m_eggTexture));
		m_eggs.back()->setTextureRectangle(rectangle(vector(),width,height));
		m_eggs.back()->setOrigin(vector(width/2, height/2));
		m_eggs.back()->setScale(m_theEggScale);
		m_eggs.back()->setLayer(6);
	}
	else
		m_eggAnimation->ChangeAnimation(0,1);

	updateEggPositions();
}
void nest::removeEgg()
{
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
	m_hatchCount = 0;
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
		m_hatchCount++;
		m_hatchlings.back()->m_sprite->setLayer(4 + i);
		
	}

	m_hatching = false;
	m_egging = false;
	m_noEggs = false;
	m_theEgg->setPosition(m_eggPosition);
	m_eggAnimation->ChangeAnimation(0,1);
	m_scale = m_theEggScale;
	m_theEgg->setScale(m_scale);
	m_theEgg->setLayer(6);
	m_flamCount = 0;
}
#include "enemy.h"

using namespace al;

enemy::enemy(collision* Collide, gui* Gui, particleEngine* ParticleEngine)
{
	m_particleEngine = ParticleEngine;
	m_enemyRotate = 5;
	m_enemyOrigin.x = 250;
	m_enemyOrigin.y = 250;
	m_enemyDownFall = 0.0f;
	m_enemyLeftFall = 0.0f;
	m_birdPhase = 0;


	// score //
	m_gui = Gui;

	m_texture = new texture("enemyAnimation.png");
	m_sprite = new sprite(m_texture);
	m_sprite->setOrigin(vector(128,128));
	m_sprite->setScale(0.5f);
	m_sprite->setLayer(10);
	

	m_animation = new animation(m_sprite, 4, 256, 256);
	m_animation->ChangeAnimation(0,2,0,5);

	m_hitbox = Collide->createHitBox(m_enemyBirdPosition,
		al::vector(m_sprite->getTransformedSize().x,
				m_sprite->getTransformedSize().y), 
		al::vector(m_sprite->getTransformedSize().x/2,
					 m_sprite->getTransformedSize().y/2),
		2);


	m_eggTexture = new texture("hatchingAnimation.png");
	m_eggSprite = new sprite(m_eggTexture);
	m_eggSprite->setLayer(10);
	m_eggSprite->setPosition(m_eggPosition);
	m_eggSprite->setTextureRectangle(rectangle(vector(),vector(256,256)));
	m_eggSprite->setOrigin(vector(m_eggSprite->getSize().x/2,m_eggSprite->getSize().y/2));

	reset();
}
enemy::~enemy()
{
#if _DEBUG
	std::cout<<"deleted enemy"<<std::endl;
#endif
	delete m_texture;
	delete m_sprite;
	delete m_eggTexture;
	delete m_eggSprite;
	delete m_animation;
	
}

void enemy::update(float DeltaTime)
{
	m_animation->update(DeltaTime);
	m_prevPosition = m_enemyBirdPosition;
	m_enemyRotate += DeltaTime*2;

	switch(m_birdPhase)
	{
	case 0: // Normal flying

		fly(DeltaTime);

		break;
	case 1: // Getting hit

		die(DeltaTime);

		break;
	case 2: // Falling
		
		fall(DeltaTime);
		
		break;
	case 3: // Happy

		happy(DeltaTime);

		break;
	case 4: // Fly back to originposition

		flyBack();

		break;

	case 5: //grab the egg

		catchEgg(DeltaTime);

		break;
	}
	
	
	m_sprite->setPosition(m_enemyBirdPosition);
	m_hitbox->Position = m_enemyBirdPosition;
}
void enemy::draw(al::viewport* Viewport)
{
	if (m_tookEgg)
		Viewport->draw(m_eggSprite);
	Viewport->draw(m_sprite);
}

void enemy::reset()
{
	m_enemyBirdPosition = -m_enemyOrigin;
	m_sprite->setPosition(m_enemyBirdPosition);
	m_hitbox->Position = m_enemyBirdPosition;
	m_enemyDownFall = 0.0f;

	m_eggPosition = vector(0,0);
	m_eggSprite->setScale(0);

	m_hitbox->isEnabled = false;
	m_timer = -float(rand()%15);
 	m_birdPhase = 2;
	m_takingEgg = false;
	m_tookEgg = false;
}

void enemy::eat(float foodValue, vector itemDirection)
{
	if(foodValue <= 0) // when boot hits enemy
	{
		m_birdPhase = 1;
		m_direction = itemDirection;
		m_animation->ChangeAnimation(2,2,2,10);
		m_hitbox->isEnabled = false;
		m_gui->addScore(m_enemyBirdPosition,50);
	}
	else // when any food hits enemy
	{
		if (m_birdPhase == 4)// stealing egg
		{
			m_animation->ChangeAnimation(4,2,4,10);
			m_gui->addScore(m_enemyBirdPosition,-100);
		}
		else // normal
		{
			m_animation->ChangeAnimation(4,2,4,10);
			m_birdPhase = 3;
			m_gui->addScore(m_enemyBirdPosition,-100);
		}
	}
}
void enemy::fly(float DeltaTime)
{
	m_prevPosition = vector(m_enemyBirdPosition);
	m_enemyDownFall += DeltaTime*5;

	if(m_enemyDownFall >= 100)
	{
		m_enemyDownFall = 100;
		if (sin(m_enemyRotate) > 0.5f && sin(2*m_enemyRotate) < 0)
		{
			m_sprite->setScale(-0.5f, 0.5f);
			m_birdPhase = 5;
		}
	}
	
	m_enemyBirdPosition = vector(m_enemyOrigin.x + 60.0f * sin(m_enemyRotate),(m_enemyOrigin.y + 100.0f * sin(2*m_enemyRotate)) + m_enemyDownFall);
	m_sprite->setRotation(5 * sin(m_enemyRotate*10));


}
void enemy::die(float DeltaTime)
{
	m_direction = ((m_enemyBirdPosition - m_prevPosition) / DeltaTime) * 1.0f + m_direction * 0.4f;
	m_timer += DeltaTime;

	if(m_timer > 0.0f)
	{
		m_birdPhase = 2;
		m_timer = -(7.0f + rand()%15);

		for (int i = 0; i < 100; ++i)
		{
			m_particleEngine->addFeather(m_enemyBirdPosition,true);
		}
	}


	//m_enemyBirdPosition.x -= 300*DeltaTime;

}
void enemy::fall(float DeltaTime)
{
	m_timer += DeltaTime;

	m_enemyBirdPosition += m_direction * DeltaTime;
	m_direction.y += 500*DeltaTime;
	m_sprite->setRotation(-5 * m_enemyRotate*15);

	if(m_timer > 0)
	{
		respawn();
		m_timer = 0;
	}
}
void enemy::happy(float DeltaTime)
{
	m_timer += DeltaTime;
	m_prevPosition = vector(m_enemyBirdPosition);
	 
	m_enemyBirdPosition = vector(m_enemyOrigin.x + 60 * sin(m_enemyRotate),m_enemyOrigin.y + 100 * sin(2*m_enemyRotate) + m_enemyDownFall );
	m_sprite->setRotation(5 * sin(m_enemyRotate*10));

	if(m_timer > 2.0f)
	{
		m_birdPhase = 0;
		m_timer = 0;
		m_animation->ChangeAnimation(0,2,0,5);
	}
}
void enemy::respawn()
{
	//m_enemyBirdPosition = vector(0, 50); 
	m_enemyRotate = -10;
	m_birdPhase = 4;
	m_animation->ChangeAnimation(0,2,0,5);
	m_sprite->setRotation(0);
	m_enemyDownFall = 0;
	m_sprite->setScale(0.5f);

	m_eggPosition = vector(0,0);
	m_eggSprite->setScale(0);
	m_takingEgg = false;
	m_tookEgg = false;
	
}
void enemy::flyBack()
{
	m_prevPosition = vector(m_enemyBirdPosition);

	m_enemyBirdPosition.x = m_enemyOrigin.x + (60 * m_enemyRotate);
	m_enemyBirdPosition.y = m_enemyOrigin.y + 100 * sin(2*m_enemyRotate);

	if (m_enemyBirdPosition.x > 0)
		m_hitbox->isEnabled = true;

	if (m_enemyBirdPosition.x > m_enemyOrigin.x)
	{
		m_birdPhase = 0;
		m_animation->ChangeAnimation(0,2,0,5);
	}
}

void enemy::catchEgg(float DeltaTime)
{

	if (sin(2*m_enemyRotate) < 0 && m_timer == 0)
		m_enemyBirdPosition = vector(m_enemyOrigin.x + 60.0f * sin(m_enemyRotate),(m_enemyOrigin.y + 100.0f * sin(2*m_enemyRotate)) + m_enemyDownFall);
	else
	{
		m_timer += DeltaTime;
		m_enemyBirdPosition = vector(m_enemyOrigin.x - m_timer*200.0f,(m_enemyOrigin.y + 200.0f * sin(-1*m_enemyRotate)) + m_enemyDownFall);
			m_eggPosition = m_enemyBirdPosition;

		if(m_timer > 0.9f)
		{
			if (!m_tookEgg)
			{
				m_takingEgg = true;
				m_tookEgg = true;
				m_hitbox->isEnabled = false;
			}
			m_eggSprite->setPosition(vector(m_eggPosition.x,m_eggPosition.y + 45));
			m_eggSprite->setScale(0.2f);
		}

		if (m_timer > 10)
		{
			m_timer = 0;
			respawn();
		}
	}
}
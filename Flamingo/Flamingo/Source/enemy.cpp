#include "enemy.h"

using namespace al;

enemy::enemy(collision* Collide, gui* Gui)
	: m_timer(0)
{
	m_enemyRotate = 5;
	m_enemyOrigin.x = 250;
	m_enemyOrigin.y = 300;
	m_birdPhase = 0;

	// score //
	m_gui = Gui;

	m_texture = new texture("enemyAnimation.png");
	m_sprite = new sprite(m_texture);
	m_sprite->setPosition(vector(m_enemyOrigin.x, m_enemyOrigin.y));
	m_sprite->setOrigin(vector(128,128));
	m_sprite->setScale(0.5f);
	m_sprite->setLayer(1);
	

	m_animation = new animation(m_sprite, 4, 256, 256);
	m_animation->ChangeAnimation(0,2,0,5);

	m_hitbox = Collide->createHitBox(m_enemyBirdPosition,
		al::vector(m_sprite->getTransformedSize().x,
				m_sprite->getTransformedSize().y), 
		al::vector(m_sprite->getTransformedSize().x/2,
					 m_sprite->getTransformedSize().y/2),
		2);

}

enemy::~enemy()
{
	std::cout<<"deleted enemy"<<std::endl;
	delete m_texture;
	delete m_sprite;
	delete m_animation;
}

void enemy::update(float DeltaTime)
{
	m_animation->update(DeltaTime);
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

		flyBack(DeltaTime);

		break;
	}
	
	
	m_sprite->setPosition(m_enemyBirdPosition);
	m_hitbox->Position = m_enemyBirdPosition;
}

void enemy::draw(al::viewport* Viewport)
{
	Viewport->draw(m_sprite);
}

void enemy::eat(float foodValue, vector itemDirection)
{
	if(foodValue == 0) // when boot hits enemy
	{
		m_birdPhase = 1;
		m_direction = itemDirection;
		m_animation->ChangeAnimation(2,2,2,10);
		m_hitbox->isEnabled = false;
		m_gui->SCORE += 50;
	}
	else // when any food hits enemy
	{
		m_animation->ChangeAnimation(4,2,4,10);
		m_birdPhase = 3;
		m_gui->SCORE -= 9000;
	}
}

void enemy::fly(float DeltaTime)
{
	m_prevPosition = vector(m_enemyBirdPosition);
	 
	
	m_enemyBirdPosition = vector(m_enemyOrigin.x + 60 * sin(m_enemyRotate),m_enemyOrigin.y + 100 * sin(2*m_enemyRotate) );
	m_sprite->setRotation(5 * sin(m_enemyRotate*10));


}

void enemy::die(float DeltaTime)
{
	m_direction = ((m_enemyBirdPosition - m_prevPosition) / DeltaTime) * 1.0f + m_direction * 0.4f;
	m_timer += DeltaTime;
	if(m_timer > 0.0f)
	{
		m_birdPhase = 2;
		m_timer = -(4.0f + rand()%10);
	}

	m_enemyBirdPosition.x -= 300*DeltaTime;

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
	 
	m_enemyBirdPosition = vector(m_enemyOrigin.x + 60 * sin(m_enemyRotate),m_enemyOrigin.y + 100 * sin(2*m_enemyRotate) );
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
	m_animation->ChangeAnimation(0,2,0,10);
	m_sprite->setRotation(0);
	
}

void enemy::flyBack(float DeltaTime)
{
	//m_enemyBirdPosition.x = m_enemyOrigin.x + 60 * sin(m_enemyRotate);
	//m_enemyBirdPosition.x++;
	m_enemyBirdPosition.x = m_enemyOrigin.x + (60 * m_enemyRotate);
	m_enemyBirdPosition.y = m_enemyOrigin.y + 100 * sin(2*m_enemyRotate);
	//m_enemyBirdPosition.x += 1;
	//m_enemyBirdPosition.y += 1;
	//std::cout << "X: " << m_enemyBirdPosition.x <<  "Y: " << m_enemyBirdPosition.y << std::endl;
//
	if (m_enemyBirdPosition.x > m_enemyOrigin.x)
	{
		m_birdPhase = 0;
		m_hitbox->isEnabled = true;
	}
}
#include "enemy.h"

using namespace al;

enemy::enemy(sf::RenderWindow *Window, collision* Collide)
{
	window = Window;

	m_enemyRotate = 5;
	m_enemyOrigin.x = 150;
	m_enemyOrigin.y = 100;

	m_texture = new texture("enemyAnimation.png");
	m_sprite = new sprite(m_texture);
	m_sprite->setPosition(vector(m_enemyOrigin.x, m_enemyOrigin.y));
	m_sprite->setOrigin(vector(128,128));
	m_sprite->setScale(0.5f);
	m_sprite->setLayer(8);
	

	m_animation = new animation(m_sprite, 4, 256, 256);

	m_hitbox = Collide->createHitBox(m_enemyBirdPosition,
		sf::Vector2f(m_sprite->getTransformedSize().x,
					 m_sprite->getTransformedSize().y), 
		sf::Vector2f(m_sprite->getTransformedSize().x/2,
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
	m_enemyBirdPosition = m_enemyOrigin;
	m_animation->update(DeltaTime);
	m_enemyRotate += DeltaTime*100;
	//enemyBird.setPosition(enemyBirdPosition);
	//m_enemyBird->setRotation(m_enemyRotate);
	m_hitbox->Position = m_enemyBirdPosition;

}

void enemy::draw(al::viewport* Viewport)
{
	Viewport->draw(m_sprite);
}
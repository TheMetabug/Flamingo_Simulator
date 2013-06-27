#include "enemy.h"

enemy::enemy(sf::RenderWindow *Window, collision* Collide)
{
	window = Window;

	m_enemyRotate = 5;
	m_enemyOrigin.x = 150;
	m_enemyOrigin.y = 100;
	
	m_enemyTexture = new sf::Texture();
	m_enemyTexture->loadFromFile("Assets/enemyAnimation.png");
	m_enemyTexture->setSmooth(true);
	m_enemyBird = new sf::Sprite();
	m_enemyBird->setTexture(*m_enemyTexture);
	m_enemyBird->setPosition(m_enemyOrigin);
	m_enemyBird->setOrigin(sf::Vector2f(128,128));
	m_enemyBird->setScale(0.5f, 0.5f);

	m_animation = new animation(m_enemyBird, 4, 256, 256);

	m_hitbox = Collide->createHitBox(m_enemyBirdPosition,
		sf::Vector2f(m_enemyBird->getGlobalBounds().width,
					 m_enemyBird->getGlobalBounds().height), 
		sf::Vector2f(m_enemyBird->getGlobalBounds().width/2,
					 m_enemyBird->getGlobalBounds().height/2),
		2);

}

enemy::~enemy()
{
	std::cout<<"deleted enemy"<<std::endl;
	delete m_animation;
}

void enemy::update(float DeltaTime)
{
	m_enemyBirdPosition = m_enemyOrigin;
	m_animation->update(DeltaTime);
	m_enemyRotate += DeltaTime*100;
	//enemyBird.setPosition(enemyBirdPosition);
	m_enemyBird->setRotation(m_enemyRotate);
	m_hitbox->Position = m_enemyBirdPosition;

}

void enemy::draw()
{
	window->draw(*m_enemyBird);
}
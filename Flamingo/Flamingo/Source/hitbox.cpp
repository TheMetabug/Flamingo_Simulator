#include "hitbox.h"

hitbox::hitbox(sf::Vector2f _Position, sf::Vector2f _Size, bool _isEnabled)
{
	Position = _Position;
	Size = _Size;
	isEnabled = _isEnabled;

}

hitbox::~hitbox()
{

}

void udpate(sf::Time DeltaTime)
{

}

collision::collision()
{

}

collision::~collision()
{

}

void collision::headPickup()
{

}
void collision::pickupHatchling()	{}
void collision::pickupEnemy()		{}
void collision::headEnemy()			{}

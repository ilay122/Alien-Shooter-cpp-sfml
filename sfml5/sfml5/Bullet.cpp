#include "Bullet.h"


Bullet::Bullet(int angle, sf::Sprite shape)
{
	this->shape = shape;

	this->pos = shape.getPosition();

	shape.setPosition(pos);
	shape.setRotation(angle);

	float rad = angle *Pi / 180;

	vel.x = bulletSpeed*(cos(rad));
	vel.y = bulletSpeed*(sin(rad));
}


Bullet::~Bullet()
{

}
bool Bullet::update(sf::Sprite map){

	shape.move(vel);
	pos = shape.getPosition();
	
	
	if (!shape.getGlobalBounds().intersects(map.getGlobalBounds()))
		return true;
	
	return false;

}
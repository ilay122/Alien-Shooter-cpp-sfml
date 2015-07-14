#include "Monster.h"


Monster::Monster(sf::Texture* texture)
{
	this->health = 5;
	std::srand(std::time(0));

	tex = texture;
	shape.setTexture((*tex));
	sf::Vector2f pos;
	pos.x = 1500;
	pos.y = rand() % 1900;
	shape.setPosition(pos);

	float angle = std::rand() % 361;
	shape.setRotation(angle);

	float rad = angle *pii / 180;

	vel.x = monsterSpeed*(cos(rad));
	vel.y = monsterSpeed*(sin(rad));
}


Monster::~Monster()
{
}

void Monster::update(sf::Sprite& map,Player& player){
	shape.move(vel);
	if (!shape.getGlobalBounds().intersects(map.getGlobalBounds())){
		float dx = player.shape.getPosition().x - shape.getPosition().x;
		float dy = player.shape.getPosition().y - shape.getPosition().y;
		double angle = (atan2(dy, dx)) * 180 / pii;
		shape.setRotation(angle);
		float rad = angle *pii / 180;

		vel.x = monsterSpeed*(cos(rad));
		vel.y = monsterSpeed*(sin(rad));
	}
}
void Monster::draw(sf::RenderWindow& win){
	win.draw(shape);
}
void Monster::gotHit(){
	health--;
}
bool Monster::isAlive(){
	return health > 0;
}
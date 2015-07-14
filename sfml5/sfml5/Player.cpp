#include "player.h"


Player::Player()
{

	tex.loadFromFile("player.png");
	shape.setTexture(tex);
	shape.setPosition(startpos);

	bullettex.loadFromFile("bullet.png");
	bulletshape.setTexture(bullettex);

	shape.setOrigin(sf::Vector2f(60, 41));
	notpressedbefore = false;

	isAlive = true;
}


Player::~Player()
{
}
void Player::update(Monsters& monsters,sf::Keyboard& keyb, sf::Mouse& mous, sf::RenderWindow& win,sf::Sprite map){
	

	sf::Vector2i curpos = mous.getPosition(win);
	
	sf::Vector2f worldPos = win.mapPixelToCoords(curpos);
	sf::Vector2f playpos = shape.getPosition();
	float dx = playpos.x - worldPos.x;
	float dy = playpos.y - worldPos.y;

	double angle = (atan2(dy, dx)) * 180 / PI;
	shape.setRotation(angle + 180);

	if (keyb.isKeyPressed(keyb.W)){
		shape.move(sf::Vector2f(0, -playerSpeed));
	}
	if (keyb.isKeyPressed(keyb.S)){
		shape.move(sf::Vector2f(0, playerSpeed));
	}
	if (keyb.isKeyPressed(keyb.D)){
		shape.move(sf::Vector2f(playerSpeed, 0));
	}
	if (keyb.isKeyPressed(keyb.A)){
		shape.move(sf::Vector2f(-playerSpeed, 0));
	}
	bool eh = false;
	float rot = shape.getRotation();
	shape.setRotation(0);
	if (shape.getPosition().x <= 0 || shape.getPosition().x + shape.getGlobalBounds().width >= map.getGlobalBounds().width || shape.getPosition().y <= 0 || shape.getPosition().y + shape.getGlobalBounds().height>= map.getGlobalBounds().height){
		eh = true;
	}
	shape.setRotation(rot);
	if (eh){
		shape.setPosition(lastpos);
	}
	else{
		lastpos = shape.getPosition();
	}
	if (monsters.killedPlayer((*this))){
		isAlive = false;
	}

	if (mous.isButtonPressed(mous.Left) && !notpressedbefore){
		bulletshape.setPosition(shape.getPosition());
		bulletshape.setRotation(angle+180);
		Bullet shot(angle + 180, bulletshape);
		bulletsshot.push_back(shot);
	}
	notpressedbefore = mous.isButtonPressed(mous.Left);
	
	
	
	for (int i = 0; i < bulletsshot.size(); i++){
		if (monsters.bulletHit(bulletsshot[i])){
			bulletsshot.erase(bulletsshot.begin() + i);
		}
		else{
			bool destroyed = bulletsshot[i].update(map);
			if (destroyed){
				bulletsshot.erase(bulletsshot.begin() + i);
			}
		}
	}
	
	sf::View view = win.getDefaultView();
	view.setCenter(shape.getPosition());
	win.setView(view);

}
void Player::draw(sf::RenderWindow& win){

	for (int i = 0; i < bulletsshot.size(); i++){
		win.draw(bulletsshot[i].shape);
	}
	win.draw(shape);
}
bool Player::isItAlive(){
	return this->isAlive;
}
void Player::reset(){
	shape.setPosition(startpos);
	shape.setRotation(0);
	bulletsshot.clear();
	isAlive = true;
}
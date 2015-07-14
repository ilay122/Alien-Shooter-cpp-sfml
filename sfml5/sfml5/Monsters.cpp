#include "Monsters.h"


Monsters::Monsters()
{
	tex.loadFromFile("monster.png");
	score = 0;
}


Monsters::~Monsters()
{
}
void Monsters::update(Player& player,sf::Sprite& map){
	for (int i = 0; i < monsters.size(); i++){
		if (!monsters[i].isAlive()){
			monsters.erase(monsters.begin() + i);
			score++;
		}
		else{
			monsters[i].update(map, player);
		}
	}
	
	time = clock.getElapsedTime().asMilliseconds();
	if (time >= everytime){
		time = 0;
		clock.restart();
		Monster monster(&tex);
		monsters.push_back(monster);
	}
}
void Monsters::draw(sf::RenderWindow& win){
	for (int i = 0; i < monsters.size(); i++){
		monsters[i].draw(win);
	}
}
bool Monsters::bulletHit(Bullet& bul){
	for (int i = 0; i < monsters.size(); i++){
		if (monsters[i].shape.getGlobalBounds().intersects(bul.shape.getGlobalBounds())){
			monsters[i].gotHit();
			return true;
		}
	}
	return false;
}
bool Monsters::killedPlayer(Player& player){
	for (int i = 0; i < monsters.size(); i++){
		if (monsters[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds())){
			return true;
		}
	}
	return false;
}
int Monsters::getScore(){
	return this->score;
}
void Monsters::reset(){
	monsters.clear();
	score = 0;
	time = 0;
}
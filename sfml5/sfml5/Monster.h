#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
const float monsterSpeed = 3.f;
const float pii = 3.14159265;
struct Player;
class Monster
{
public:
	sf::Sprite shape;
	sf::Vector2f vel;
	Monster(sf::Texture* texture);
	~Monster();
	void update(sf::Sprite& map, Player& player);
	void draw(sf::RenderWindow& win);
	bool isAlive();
	void gotHit();
	
private:
	sf::Texture* tex;
	int health;
	
};


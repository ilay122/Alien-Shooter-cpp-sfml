#pragma once
#include "Monster.h"
#include "Player.h"
#include "vector"
#include <SFML/Graphics.hpp>
#include "Bullet.h"
struct Monster;
struct Player;

const int everytime = 3000;
class Monsters
{
public:
	std::vector<Monster> monsters;
	Monsters();
	~Monsters();
	void update(Player& player,sf::Sprite& map);
	void draw(sf::RenderWindow& win);
	bool bulletHit(Bullet& bul);
	int getScore();
	bool killedPlayer(Player& player);
	void reset();
private:
	sf::Clock clock;
	int time = 0;
	sf::Texture tex;
	int score;
};


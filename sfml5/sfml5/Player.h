#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Bullet.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include "Monsters.h"
struct Monsters;
const float playerSpeed = 8;
#define PI 3.14159265
const sf::Vector2f startpos(500,500);
class Player
{
public:
	std::vector<Bullet> bulletsshot;
	sf::Sprite shape;
	bool notpressedbefore;

	Player();
	~Player();
	void update(Monsters& monsters,sf::Keyboard&, sf::Mouse&, sf::RenderWindow&,sf::Sprite map);
	void draw(sf::RenderWindow&);
	bool isItAlive();
	void reset();
private:
	bool isAlive;
	sf::Texture tex;
	sf::Texture bullettex;
	sf::Sprite bulletshape;
	sf::Vector2f lastpos;
};

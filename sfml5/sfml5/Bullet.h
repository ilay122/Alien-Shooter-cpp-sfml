#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

const float bulletSpeed = 11.f;
const float Pi = 3.14159265;
class Bullet
{
public:
	sf::Vector2f pos;
	sf::Vector2f vel;
	sf::Sprite shape;
	Bullet(int angle, sf::Sprite);
	~Bullet();
	bool update(sf::Sprite map);
private:
	sf::Texture tex;
};

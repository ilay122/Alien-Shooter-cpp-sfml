#pragma once
#include "Player.h"
#include "Monsters.h"
#include <SFML/Graphics.hpp>
class HUD
{
public:
	Player* player;
	Monsters* monsters;
	HUD(Player* player, Monsters* monsters);
	void update(sf::RenderWindow& win);
	void draw(sf::RenderWindow& win);
	~HUD();
private:
	sf::Texture bg;
	sf::Sprite map;

	sf::Texture pictex;
	sf::Sprite pic;

	int state;
	int hover;
	sf::Font font;
	sf::Text text1;
	sf::Text text2;
	sf::Text pauseText;
	sf::Text scoretext;

	bool escapePressed;
};


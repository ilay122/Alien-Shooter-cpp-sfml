#include "HUD.h"


HUD::HUD(Player* player, Monsters* monsters)
{
	font.loadFromFile("Snowstorm.ttf");
	this->player = player;
	this->monsters = monsters;

	bg.loadFromFile("bg.png");
	bg.setRepeated(true);
	sf::Sprite map(bg, sf::IntRect(0, 0, 1800, 1600));
	this->map = map;

	pictex.loadFromFile("zombie.png");
	
	pic.setTexture(pictex);
	pic.setScale(1.4f,1.4f);
	pic.setPosition(sf::Vector2f(160, 70));

	text1.setFont(font);
	text2.setFont(font);
	scoretext.setFont(font);
	pauseText.setFont(font);

	text1.setCharacterSize(40);
	text2.setCharacterSize(40);
	scoretext.setCharacterSize(40);
	pauseText.setCharacterSize(22);

	text1.setPosition(375, 300);
	text2.setPosition(375, 400);

	text1.setColor(sf::Color::Black);
	text2.setColor(sf::Color::Black);
	

	text1.setString("Play");
	text2.setString("Quit");
	

	state = 0;
	hover = 0;
}


HUD::~HUD()
{
}

void HUD::update(sf::RenderWindow& win){
	
	//state 0-menu,1-playing 2-pause 3-lost
	sf::Keyboard keyb = sf::Keyboard();
	sf::Mouse mous = sf::Mouse();
	
	sf::Vector2i curpos = mous.getPosition(win);

	sf::Vector2f worldPos = win.mapPixelToCoords(curpos);
	switch (state)
	{
	case 0:{
		win.setView(win.getDefaultView());
		if (text1.getGlobalBounds().contains(worldPos.x, worldPos.y)){
			text1.setStyle(text1.Underlined);
			if (mous.isButtonPressed(mous.Left)){
				state = 1;
			}
		}
		else{
			text1.setStyle(text1.Regular);
		}

		if (text2.getGlobalBounds().contains(worldPos.x, worldPos.y)){
			text2.setStyle(text2.Underlined);
			if (mous.isButtonPressed(mous.Left)){
				win.close();
			}
		}
		else{
			text2.setStyle(text2.Regular);
		}

		break;
	}
	case 1:{
		if (!player->isItAlive()){
			state = 3;
		}
		else{
			player->update((*monsters), keyb, mous, win, map);
			monsters->update((*player), map);
			
			scoretext.setString("Score : " + std::to_string(monsters->getScore()));
			if (!escapePressed && sf::Keyboard().isKeyPressed(sf::Keyboard().Escape)){
				state = 2;
			}
			escapePressed = sf::Keyboard().isKeyPressed(sf::Keyboard().Escape);
			scoretext.setPosition(player->shape.getPosition().x-400, player->shape.getPosition().y - 300);
			
		}
		break;
	}
	case 2:{
		pauseText.setPosition(player->shape.getPosition().x-130, player->shape.getPosition().y - 100);
		pauseText.setString("press left mouse to continue and \n escape to return to menu");
		if (mous.isButtonPressed(mous.Left)){
			state = 1;
		}
		if (!escapePressed &&keyb.isKeyPressed(keyb.Escape)){
			state = 0;
			player->reset();
			monsters->reset();
		}
		break;
	}
	case 3:{
		pauseText.setPosition(player->shape.getPosition().x - 185, player->shape.getPosition().y - 150);
		pauseText.setString("you have lost press left mouse to restart \n or escape to return to menu");
		if (mous.isButtonPressed(mous.Left)){
			state = 1;
			player->reset();
			monsters->reset();
		}
		if (!escapePressed &&keyb.isKeyPressed(keyb.Escape)){
			state = 0;
			player->reset();
			monsters->reset();
		}
		break;
	}
		
	}
	escapePressed = keyb.isKeyPressed(keyb.Escape);
}
void HUD::draw(sf::RenderWindow& win){
	switch (state){
	case 0:{
		win.draw(text1);
		win.draw(text2);
		win.draw(pic);
		break;
	}
	case 1:{
		win.draw(map);
		win.draw(scoretext);
		player->draw(win);
		monsters->draw(win);
		
		break;
	}
	case 2:{
		win.draw(map);
		win.draw(scoretext);
		player->draw(win);
		monsters->draw(win);
		win.draw(pauseText);
		break;
	}
	case 3:{
		win.draw(map);
		win.draw(scoretext);
		player->draw(win);
		monsters->draw(win);
		win.draw(pauseText);
		break;
	}
	}
}
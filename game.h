#pragma once

#include "enemy.h"
#include "mainmenu.h"
#include "player.h"
#include "puzzle.h"
#include<vector>


class game {

public:
	//window
	sf::RenderWindow* window;
	sf::VideoMode vidmode;
	sf::Event ev;

	//mousepos

	//objects from other class
	Enemy enemy1, enemy2, enemy3, enemy4;
	Player* player;
	 
	//text and font
	sf::Text endGameText;
	sf::Font font1;
	sf::Font font2;
	sf::Text ingametext;
	sf::Text wintext;

	//constructor and destructors
	game();
	virtual ~game();
	
	//accessors
	const bool running() const;
	const bool getendgame() const;

	//functions
	void pollevents();
	void update();
	void render();
	
	//player func
	//void spawnenemies();
	void updateplayer();
	bool updatecombat(const sf::FloatRect& rect1, const sf::FloatRect& rect2);
	void updatecollision();
	void renderplayer();
	void renderenemy();
	void startcombat();
	const sf::RenderWindow& getWindow() const;

	//world
	sf::Sprite background;
	sf::Texture backgroundtex;
	sf::Sprite door;
	sf::Texture doortex;

	//puzzle

private:
	//game logic
	bool endgame;
	bool ingame;
	bool collide;
	int playerhealth;
	int cooldownmax;
	int cooldown;
	bool wingame;

	//private func
	void initvar();
	void initwindow();
	void initworld();
	void initplayer();
	void inittext();
	void initfonts();
	void initenemies();

};

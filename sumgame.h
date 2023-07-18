#pragma once

#include"player.h"
//#include "Puzzle.h"

class sumgame
{
private:
	sf::RenderWindow window;
	sf::Event ev;

	Player* player;
	//	Puzzle* puzzle;

	sf::Sprite bg;
	sf::Texture bgtext;
	sf::Font font;
	sf::Text text;
	sf::Color color = sf::Color(60, 70, 70, 0);
	void initWindow();
	void initPlayer();
	//void initPuzzle();

public:

	//Functions
	bool endgame;

	sumgame();
	virtual ~sumgame();

	//Functions
	void updatePlayer();
	void updateCollision();
	void update();
	void renderPlayer();
	void render();
	//	void renderPuzzle();
	const sf::RenderWindow& getWindow() const;
};


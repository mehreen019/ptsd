#include "stdx.h"
#include "game.h"
#include "sumgame.h"

int main(void) {

	sf::Music music;
	if (!music.openFromFile("music.wav")) {
		std::cout << "COULDN'T OPEN MUSIC FILE\n";
	}
	music.play();
	music.setLoop(true);
	
	Menu* menu = new Menu();
	menu->run_menu();
	
	if (menu->winrun) {
		puzzle Puzzle;
		bool win = Puzzle.wordpuzzle();

		if(win){
		sumgame gamee;
		while (gamee.getWindow().isOpen())
		{
			gamee.update();
			gamee.render();
		}
		if (!gamee.endgame) {

			bool win2 = Puzzle.npuzzle(win);
			//Enemy enemy1, enemy2, enemy3, enemy4;

			game Game;
			while (Game.running() && win2) {

				Game.update();

				Game.render();

			}
		}
		}
	}
	delete menu;
	menu = nullptr;

	return 0;

}





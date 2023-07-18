#include "stdx.h"
#include "game.h"

int i = 0;

//init func
void game::initvar() {
	
	this->window = nullptr;
	this->endgame = false;
	this->ingame = true;
	this->playerhealth = 20;
	this->cooldownmax = 50;
	this->cooldown = 0;
	this->collide = false;

}

void game::initwindow() {
	this->vidmode.height = 720;
	this->vidmode.width = 1280;

	this->window = new sf::RenderWindow(this->vidmode, "combat", sf::Style::Titlebar | sf::Style::Close);
	this->window->setPosition(sf::Vector2i(300, 100));

	this->window->setFramerateLimit(60);

}

void game::initfonts()
{
	if (!this->font1.loadFromFile("HelpMe.otf"))
	{
		std::cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD HelpMe.otf" << "\n";
	}
	if (!this->font2.loadFromFile("Fonts/PixellettersFull.ttf"))
	{
		std::cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD PixellettersFull.ttf" << "\n";
	}
}

void game::inittext()
{
	//End game text
	this->endGameText.setFont(this->font1);
	this->endGameText.setFillColor(sf::Color::Red);
	this->endGameText.setCharacterSize(60);
	this->endGameText.setPosition(sf::Vector2f(400, 300));
	this->endGameText.setString("YOU DIED\nPress ESC to exit");

	this->ingametext.setFont(this->font2);
	this->ingametext.setFillColor(sf::Color::Black);
	this->ingametext.setStyle(sf::Text::Bold);
	this->ingametext.setCharacterSize(65);
	this->ingametext.setPosition(sf::Vector2f(300, 300));
	this->ingametext.setString("Avoid enemies and reach the door!\nPress F to continue");

	this->wintext.setFont(this->font1);
	this->wintext.setFillColor(sf::Color::Black);
	this->wintext.setCharacterSize(65);
	this->wintext.setPosition(sf::Vector2f(300, 300));
	this->wintext.setString("CONGRATULATIONS!!\nYOU ESCAPED!!\nPress ESC to quit");

}

void game::initplayer() {
	this->player = new Player();
}

void game::initworld() {
	if (!this->backgroundtex.loadFromFile("map.png"))
		std::cout << "ERROR LOADING BACKGROUND\n";
	this->background.setTexture(this->backgroundtex);

	if (!this->doortex.loadFromFile("door.png"))
		std::cout << "ERROR LOADING BACKGROUND\n";
	this->door.setTexture(this->doortex);
	this->door.setPosition(sf::Vector2f(1200.f, 300.f));
	this->door.setScale(sf::Vector2f(1.5f, 1.5f));
	
}

void game::initenemies() {
	this->enemy1.initen(300, 300, 50.0f, sf::Vector2f(2.0f, 2.0f));
	this->enemy2.initen(500, 200, 50.0f, sf::Vector2f(2.0f, 2.0f));
	this->enemy3.initen(700, 200, 50.0f, sf::Vector2f(2.0f, 2.0f));
	this->enemy4.initen(60, 200, 50.0f, sf::Vector2f(2.0f, 2.0f));

	this->enemy1.enemydraw();
	this->enemy2.enemydraw();
	this->enemy3.enemydraw();
	this->enemy4.enemydraw();
}

//construct and destruct
game::game() {
	this->initvar();
	this->initwindow();
	this->initworld();
	this->initplayer();
	this->inittext();
	this->initfonts();
	this->initenemies();
}

game::~game() {
	delete this->window;
}

//accessors
const bool game::running() const {
	return this->window->isOpen();
}

const bool game::getendgame() const{
	return this->endgame;
}


//update func

void game::pollevents() {

	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
				break;
			}
			else if (
				this->ev.key.code == sf::Keyboard::A ||
				this->ev.key.code == sf::Keyboard::D ||
				this->ev.key.code == sf::Keyboard::W ||
				this->ev.key.code == sf::Keyboard::S
				) 
			{
				this->player->resetAnimationTimer();
			}
			else if (
				this->ev.key.code == sf::Keyboard::F
				)
			{
				ingame = false;
			}
		}
	}
}

void game::updateplayer()
{
	this->player->update();
}

void game::updatecollision()
{
	//Collision bottom of screen
	if (this->player->getPosition().y + this->player->getGlobalBounds().height > this->window->getSize().y)
	{
		this->player->resetVelocityY();
		this->player->setPosition(
			this->player->getPosition().x,
			this->window->getSize().y - this->player->getGlobalBounds().height
		);
	}
	if (this->player->getGlobalBounds().left <= 0.f)
		this->player->setPosition(0.f, this->player->getGlobalBounds().top);

	if (this->player->getGlobalBounds().left + this->player->getGlobalBounds().width >= this->window->getSize().x)
		this->player->setPosition(this->window->getSize().x - this->player->getGlobalBounds().width, this->player->getGlobalBounds().top);
	//Top
	if (this->player->getGlobalBounds().top <= 0.f)
		this->player->setPosition(this->player->getGlobalBounds().left, 0.f);
	//Bottom
	if (this->player->getGlobalBounds().top + this->player->getGlobalBounds().height >= this->window->getSize().y)
		this->player->setPosition(this->player->getGlobalBounds().left, this->window->getSize().y - this->player->getGlobalBounds().height);

	if (this->player->getGlobalBounds().intersects(this->door.getGlobalBounds())) {
		wingame = true;
	}

}

bool game::updatecombat(const sf::FloatRect& rect1, const sf::FloatRect& rect2) {
	if (rect1.intersects(rect2)) {
		this->endgame = true;
		return true;
	}
	else return false;
	}
//}

void game::startcombat() {
	if (this->updatecombat(this->player->getGlobalBounds(), enemy1.getglobalbounds())) {
		this->collide = true;
	}
	if (this->updatecombat(this->player->getGlobalBounds(), enemy2.getglobalbounds())) {
		this->collide = true;
	}
	if (this->updatecombat(this->player->getGlobalBounds(), enemy3.getglobalbounds())) {
		this->collide = true;
	}
	if (this->updatecombat(this->player->getGlobalBounds(), enemy4.getglobalbounds())) {
		this->collide = true;
	}
}


void game::update() {
	this->pollevents();
	
	//if (this->endgame == false)
	{
		this->updateplayer();
		//this->spawnenemies();
		this->updatecollision();
		if(!wingame)this->startcombat();		
		//this->updatecombat();
	}
	
}

void game::renderplayer()
{
	this->player->render(*this->window);
}

void game::renderenemy() 
{
	enemy1.enrender();
	enemy2.enrender();
	enemy3.enrender();
	enemy4.enrender();
	this->window->draw(enemy1.enemysprite);
	this->window->draw(enemy2.enemysprite);
	this->window->draw(enemy3.enemysprite);
	this->window->draw(enemy4.enemysprite);

}

void game::render() {

	this->window->clear();
	this->window->draw(this->background);
	this->window->draw(this->door);
	
	if (ingame) {
		this->window->draw(this->ingametext);
	}

	if (!ingame) {
		if(!collide && !wingame)this->renderplayer();
		this->renderenemy();
		if (this->getendgame())
		{
			this->window->draw(this->endGameText);
			this->pollevents();
		}
		if (wingame)
			this->window->draw(this->wintext);
	}

	this->window->display();
}

const sf::RenderWindow& game::getWindow() const
{
	return *this->window;
}


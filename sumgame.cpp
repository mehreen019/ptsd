#include"stdx.h"
#include "sumgame.h"
//#include "Puzzle.h"

void sumgame::initWindow()
{
	this->window.create(sf::VideoMode(1280, 720), "Game", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(144);
	this->window.setPosition(sf::Vector2i(300.f, 100.f));
	this->bgtext.loadFromFile("images/map.png");
	this->bg.setTexture(bgtext);
	this->endgame = false;
	if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf")) {
		std::cout << "ERROR LOADING FONT FOR SUMGAME";
	}
	this->text.setFont(font);
	this->text.setFillColor(sf::Color::White);
	this->text.setString("Go through the door\nto encounter the next puzzle");
	// about.setOutlineThickness(1);
	this->text.setCharacterSize(80);
	this->text.setPosition(400, 400);

}

void sumgame::initPlayer()
{
	this->player = new Player();
}

sumgame::sumgame()
{
	this->initWindow();
	this->initPlayer();
	//this->initPuzzle();
}

sumgame::~sumgame()
{
	delete this->player;
	//delete this->puzzle;
}

void sumgame::updatePlayer()
{
	this->player->update();
}

void sumgame::updateCollision()
{
	//Collision bottom of screen
	if (this->player->getPosition().y + this->player->getGlobalBounds().height > this->window.getSize().y)
	{
		this->player->resetVelocityY();
		this->player->setPosition(
			this->player->getPosition().x,
			this->window.getSize().y - this->player->getGlobalBounds().height
		);
	}
	if (this->player->getGlobalBounds().left <= 0.f)
		this->player->setPosition(0.f, this->player->getGlobalBounds().top);

	if (this->player->getGlobalBounds().left + this->player->getGlobalBounds().width >= this->window.getSize().x)
	{
		this->player->setPosition(this->window.getSize().x - this->player->getGlobalBounds().width, this->player->getGlobalBounds().top);
		this->window.close();
	}
	//Top
	if (this->player->getGlobalBounds().top <= 0.f)
		this->player->setPosition(this->player->getGlobalBounds().left, 0.f);
	//Bottom
	if (this->player->getGlobalBounds().top + this->player->getGlobalBounds().height >= this->window.getSize().y)
		this->player->setPosition(this->player->getGlobalBounds().left, this->window.getSize().y - this->player->getGlobalBounds().height);

}

void sumgame::update()
{
	//Polling window events
	while (this->window.pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed) {
			this->window.close();
			endgame = true;
		}
		else if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape) {
			this->window.close();
			endgame = true;
		}

		if (
			this->ev.type == sf::Event::KeyReleased &&
			(
				this->ev.key.code == sf::Keyboard::A ||
				this->ev.key.code == sf::Keyboard::D ||
				this->ev.key.code == sf::Keyboard::W ||
				this->ev.key.code == sf::Keyboard::S
				)
			)
		{
			this->player->resetAnimationTimer();
		}
	}

	this->updatePlayer();

	this->updateCollision();



}

void sumgame::renderPlayer()
{
	this->player->render(this->window);
}


void sumgame::render()
{
	this->window.clear(this->color);
	//const sf::Color &color = sf::Color(0,0,0,225)
	this->window.draw(bg);
	//Render game

	this->renderPlayer();
	//this->renderPuzzle();

	sf::Texture doorTexture;
	if (!doorTexture.loadFromFile("door.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
	}
	sf::Sprite door;

	door.setTexture(doorTexture);

	//Resize the sprite
	door.scale(2.f, 2.f);
	door.setPosition(1180, 200);
	//
	this->window.draw(door);
	this->window.draw(this->text);
	this->window.display();
}

const sf::RenderWindow& sumgame::getWindow() const
{
	return this->window;
}
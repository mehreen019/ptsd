#include "stdx.h"
#include "enemy.h"

void Enemy::updatePosition(float deltaTime) {
        // Update the position based on speed, direction, and deltaTime
       this->position += this->direction * this->speed * deltaTime;
       //std::cout <<" "<< position.x;
        
        // Check if the enemy reached the edge of the screen
        if (this->position.x < 0 || this->position.x > 900.f || this->position.y < 0 || this->position.y > 700.f) {
            // Reverse the direction of the enemy
            direction = -direction;
        }
}

void Enemy::initen(float x, float y, float speed, sf::Vector2f direction) {
    this->position = sf::Vector2f(x,y);
    this->speed = speed;
    this->direction = direction;
}


Enemy::Enemy() {}


void Enemy::enemydraw() {
    this->enemytex.loadFromFile("enemyy.png");
    this->enemysprite.setTexture(enemytex);
    this->enemysprite.setScale(sf::Vector2f(1.5f, 1.5f));
    this->enemysprite.setPosition(300.f, 200.f);
}

void Enemy::enrender() {
    this->updatePosition(0.016f);
    this->enemysprite.setPosition(this->getPosition());
    //std::cout << " " << this->getPosition().y;
    //this->Gamee.window->draw(this->enemysprite);
}

const sf::FloatRect Enemy::getglobalbounds() const
{   
    sf::FloatRect bounds(position.x, position.y, enemysprite.getLocalBounds().width, enemysprite.getLocalBounds().height);
    return bounds;
    //return this->enemysprite.getGlobalBounds();
}

sf::Vector2f Enemy::getPosition() const {
        return position;
}

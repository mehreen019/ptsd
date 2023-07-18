/*#pragma once

class Enemy
{
private:
    sf::Texture enemytex;
    sf::Sprite enemysprite;

    void initen(const sf::RenderWindow& window);

public:
    Enemy(const sf::RenderWindow& window);
    virtual ~Enemy();

    const sf::FloatRect getbounds() const;

    //Functions
    void update();
    void render(sf::RenderTarget& target);
};
*/


#pragma once


class Enemy {
public:

    Enemy();
    void updatePosition(float deltaTime);
    sf::Vector2f getPosition() const;
    void initen(float x, float y, float speed, sf::Vector2f direction);
    sf::Texture enemytex;
    sf::Sprite enemysprite;
    void enemydraw();
    void enrender();
    const sf::FloatRect getglobalbounds() const;
  
private:

    sf::Vector2f position;
    float speed;
    sf::Vector2f direction;
};

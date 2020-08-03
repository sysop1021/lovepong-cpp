#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include "Paddle.h"

class Ball
{
public:
    Ball(float x, float y, float w, float h);
    ~Ball();

    void update(float dt);
    void render(sf::RenderWindow& window);
    void reset(bool isP1serve);
    bool checkCollision(Paddle& paddle);

    sf::RectangleShape ball;
    sf::Vector2f size;

    float xPos;
    float yPos;
    float dX;
    float dY;

private:

};

#endif

#include "Ball.h"

Ball::Ball(float x, float y, float w, float h)
{
    xPos = x;
    yPos = y;
    //width = w;
    //height = h;
    size.x = w;
    size.y = h;

    ball.setSize(size);
    ball.setPosition(xPos, yPos);

    reset();

}

Ball::~Ball()
{

}

void Ball::update(float dt)
{
    xPos += dX * dt;
    yPos += dY * dt;

    ball.setPosition(xPos, yPos);
}

void Ball::reset()
{
    xPos = ((1280 / 2) - (size.x / 2));
    yPos = ((720 / 2) - (size.y / 2));

    // a total mess, honestly
    // randInSomeRange = (rand() % (max-min + 1)) + min;
    dX = (rand() % (2 - 1 + 1)) + 1 == 1 ? 300 : -300;
    dY = (rand() % (150 + 150 + 1)) - 150;

    ball.setPosition(xPos, yPos);
}

void Ball::render(sf::RenderWindow& window)
{
    window.draw(ball);
}


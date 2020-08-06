#include "Ball.h"

Ball::Ball(float x, float y, float w, float h)
{
    xPos = x;
    yPos = y;
    size.x = w;
    size.y = h;

    ball.setSize(size);
    ball.setPosition(xPos, yPos);

    reset(true);

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

void Ball::reset(bool isP1serve)
{
    xPos = ((1280 / 2) - (size.x / 2));
    yPos = ((720 / 2) - (size.y / 2));

    // randInSomeRange = (rand() % (max-min + 1)) + min;
    if (isP1serve)
    {
        dX = 300;
    }

    else
    {
        dX = -300;
    }

    dY = (rand() % (150 + 150 + 1)) - 150;

    ball.setPosition(xPos, yPos);
}

void Ball::render(sf::RenderWindow& window)
{
    window.draw(ball);
}

bool Ball::checkCollision(Paddle& paddle)
{
    if( !(xPos > (paddle.xPos + paddle.size.x)) &&
        !((xPos + size.x) < paddle.xPos) &&
        !(yPos > (paddle.yPos + paddle.size.y)) &&
        !((yPos + size.y) < paddle.yPos) )
    {
        return true;
    }

    else
    {
        return false;
    }
}

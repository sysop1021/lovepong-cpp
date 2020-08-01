#include "Paddle.h"

Paddle::Paddle(float x, float y, float w, float h)
{
    xPos = x;
    yPos = y;
    size.x = w;
    size.y = h;

    paddle.setSize(size);
    paddle.setPosition(xPos, yPos);
}

Paddle::~Paddle()
{

}

void Paddle::update()
{
    paddle.setPosition(xPos, yPos);
}

void Paddle::render(sf::RenderWindow& window)
{
    window.draw(paddle);
}

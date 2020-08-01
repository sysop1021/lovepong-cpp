#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

class Paddle
{
public:
    Paddle(float x, float y, float w, float h);
    ~Paddle();

    void update();
    void render(sf::RenderWindow& window);

    sf::RectangleShape paddle;
    sf::Vector2f size;

    float xPos;
    float yPos;
    float width;
    float height;
    float dY;

private:

};

#endif

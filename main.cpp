#include <SFML/Graphics.hpp>
#include <math.h>               // needed for ceil()
#include <string>               // game state identifier - should probably use c-strings
#include <iostream>

#include "Ball.h"
#include "Paddle.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const int PADDLE_SPEED = 600;
const float PADDLE_WIDTH = 15.f;
const float PADDLE_HEIGHT = 60.f;
const float PLAYER1Y = 90.f;
const float PLAYER2Y = WINDOW_HEIGHT - 150.f;
const float PADDLE_X_OFFSET = 30.f;
const float BALL_SIZE = 12.f;
const int TEXT_SIZE = 24;

int main(int argc, char* argv[])
{
    /** Initialization **/
    /* Window Setup */
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "pong-5");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true); // seems to help with the jaggedy movement
    sf::Color color(40, 45, 52);

    srand(time(0));
    std::string gameState = "start";

    /* Font/Text setup */
    sf::Font font;
    font.loadFromFile("font.ttf");

    sf::Text text("Hello, " + gameState + " state!", font);
    text.setCharacterSize(TEXT_SIZE);

    sf::FloatRect textBox = text.getGlobalBounds();
    text.setPosition((WINDOW_WIDTH / 2 - (textBox.width / 2)), 60);

    /* Paddle setup */
    Paddle p1(PADDLE_X_OFFSET, PLAYER1Y, PADDLE_WIDTH, PADDLE_HEIGHT);
    Paddle p2(WINDOW_WIDTH - PADDLE_X_OFFSET - PADDLE_WIDTH, PLAYER2Y, PADDLE_WIDTH, PADDLE_HEIGHT);

    /* Ball setup */
    Ball ball(((WINDOW_WIDTH / 2) - (BALL_SIZE / 2)), (WINDOW_HEIGHT / 2 - (BALL_SIZE / 2)), BALL_SIZE, BALL_SIZE);

    /* Scoreboard setup */
    unsigned short player1score = 0;
    unsigned short player2score = 0;

    sf::Text p1scoreboard(std::to_string(player1score), font, 100);
    p1scoreboard.setPosition(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 3);

    sf::Text p2scoreboard(std::to_string(player2score), font, 100);
    p2scoreboard.setPosition(WINDOW_WIDTH / 2 + 90, WINDOW_HEIGHT / 3);

    /* FPS Counter setup */
    sf::Text fpsCtr("FPS:", font, 25);
    fpsCtr.setFillColor(sf::Color::Green);
    fpsCtr.setPosition(5.f, 5.f);

    bool showDebug = false;

    // Used as a buffer timer so we don't update the FPS counter every frame
    float smoothTimer = 0.f;

    sf::Clock clock;

    /** Game Loop **/
    while (window.isOpen())
    {
        sf::Time dt = clock.restart();

        sf::Event event;
        while (window.pollEvent(event))

        {
            /* Game exit on Esc */
            if ((event.type == sf::Event::Closed) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }

            /* Show FPS overlay on F11 */
            if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F11))
            {
                showDebug = !showDebug;
            }

            /* Toggle game state on Enter */
            if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter))
            {
                if (gameState == "start")
                {
                    gameState = "play";
                    text.setString("Hello, " + gameState + " state!");
                }

                else
                {
                    gameState = "start";
                    text.setString("Hello, " + gameState + " state!");

                    ball.reset();
                }
            }
        }

        /** Handle Input **/
        // these silly long tertiary expressions mean I can now get rid of #include <algorithm>
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            p1.yPos = (0.f > p1.yPos - PADDLE_SPEED * dt.asSeconds() ? 0.f : p1.yPos - PADDLE_SPEED * dt.asSeconds());
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            p1.yPos = (WINDOW_HEIGHT - PADDLE_HEIGHT < p1.yPos + PADDLE_SPEED * dt.asSeconds() ? WINDOW_HEIGHT - PADDLE_HEIGHT : p1.yPos + PADDLE_SPEED * dt.asSeconds());
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            p2.yPos = (0.f > p2.yPos - PADDLE_SPEED * dt.asSeconds() ? 0.f : p2.yPos - PADDLE_SPEED * dt.asSeconds());
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            p2.yPos = (WINDOW_HEIGHT - PADDLE_HEIGHT < p2.yPos + PADDLE_SPEED * dt.asSeconds() ? WINDOW_HEIGHT - PADDLE_HEIGHT : p2.yPos + PADDLE_SPEED * dt.asSeconds());
        }

        /** Update **/
        p1.update();
        p2.update();

        if (gameState == "play")
        {
            ball.update(dt.asSeconds());
        }

        /** Draw **/
        window.clear(color);
        window.draw(text);
        window.draw(p1scoreboard);
        window.draw(p2scoreboard);
        p1.render(window);
        p2.render(window);
        ball.render(window);

        if (showDebug)
        {
            window.draw(fpsCtr);
        }

        int fps = ceil(1.f / dt.asSeconds());
        smoothTimer += dt.asMilliseconds();

        if (smoothTimer > 500.f)
        {
            fpsCtr.setString("FPS: " + std::to_string(fps));
            smoothTimer = 0.f;
        }

        window.display();
    }

    return 0;
}

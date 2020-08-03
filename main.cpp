#include <SFML/Graphics.hpp>
#include <math.h>               // needed for ceil()
#include <string>               // game state identifier - should probably use c-strings

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
const float SPEED_UP_FACTOR = 1.03f;

int main(int argc, char* argv[])
{
    /** Initialization **/
    /* Window Setup */
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "pong-9");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true); // seems to help with the jaggedy movement
    sf::Color color(40, 45, 52);

    srand(time(0));
    std::string gameState = "start";
    bool isP1serve = true;

    /* Font/Text setup */
    sf::Font font;
    font.loadFromFile("font.ttf");

    sf::Text greeting("Welcome to Pong!", font);
    greeting.setCharacterSize(TEXT_SIZE);
    sf::FloatRect greetBox = greeting.getGlobalBounds();
    greeting.setPosition((WINDOW_WIDTH / 2 - (greetBox.width / 2)), 60);

    sf::Text instruction("Press Enter to begin!", font);
    instruction.setCharacterSize(TEXT_SIZE);
    sf::FloatRect instructBox = instruction.getGlobalBounds();
    instruction.setPosition((WINDOW_WIDTH / 2 - (instructBox.width / 2)), 60 + (TEXT_SIZE * 1.25f));

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
                    gameState = "serve";
                    greeting.setString("Player 1's serve!");
                    instruction.setString("Press Enter to serve!");
                }

                else if (gameState == "serve")
                {
                    gameState = "play";
                    greeting.setString("");
                    instruction.setString("");
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

            if (ball.checkCollision(p1))
            {
                ball.dX = -ball.dX * SPEED_UP_FACTOR;
                ball.xPos = p1.xPos + p1.size.x;

                if (ball.dY > 0)
                {
                    ball.dY = (rand() % (450 - 30 + 1) + 30);
                }

                else
                {
                    ball.dY = -(rand() % (450 - 30 + 1) + 30);
                }
            }

            if (ball.checkCollision(p2))
            {
                ball.dX = -ball.dX * SPEED_UP_FACTOR;
                ball.xPos = p2.xPos - ball.size.x;

                if (ball.dY > 0)
                {
                    ball.dY = (rand() % (450 - 30 + 1) + 30);
                }

                else
                {
                    ball.dY = -(rand() % (450 - 30 + 1) + 30);
                }
            }

            if (ball.yPos <= 0)
            {
                ball.yPos = 0;
                ball.dY = -ball.dY;
            }

            if (ball.yPos + ball.size.y >= WINDOW_HEIGHT)
            {
                ball.yPos = WINDOW_HEIGHT - ball.size.y;
                ball.dY = -ball.dY;
            }

            // TODO: left and right edge catch - increment appropriate score and reset ball
            if(ball.xPos >= WINDOW_WIDTH - BALL_SIZE)
            {
                player1score++;
                p1scoreboard.setString(std::to_string(player1score));
                isP1serve = false;
                ball.reset(isP1serve);
                gameState = "serve";
                greeting.setString("Player 2's serve!");
                instruction.setString("Press Enter to serve!");
            }

            if(ball.xPos <= 0)
            {
                player2score++;
                p2scoreboard.setString(std::to_string(player2score));
                isP1serve = true;
                ball.reset(isP1serve);
                gameState = "serve";
                greeting.setString("Player 1's serve!");
                instruction.setString("Press Enter to serve!");

            }
        }

        /** Draw **/
        window.clear(color);
        window.draw(greeting);
        window.draw(instruction);
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

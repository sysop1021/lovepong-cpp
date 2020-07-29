#include <SFML/Graphics.hpp>
#include <math.h>               // needed for ceil()
#include <string>               // game state identifier - should probably use c-strings

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const int TEXT_SIZE = 24;
const int PADDLE_SPEED = 600;

int main(int argc, char* argv[])
{
    /** Initialization **/
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "pong-4");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    srand(time(0));
    std::string gameState = "start";

    /* Font/Text setup */
    sf::Font font;
    font.loadFromFile("font.ttf");

    sf::Text text("Hello, " + gameState + " state!", font);
    text.setCharacterSize(TEXT_SIZE);
    // get a rect of the text so we can halve it for centering
    sf::FloatRect textBox = text.getGlobalBounds();
    text.setPosition((WINDOW_WIDTH / 2 - (textBox.width / 2)), 60);

    // window bg color
    sf::Color color(40, 45, 52);

    /* Paddle setup */
    sf::Vector2f paddleSize(15.f, 60.f);
    sf::Vector2f ballSize(12.f, 12.f);
    float player1Y = 90.f;
    float player2Y = WINDOW_HEIGHT - 150.f;

    sf::RectangleShape p1;
    p1.setSize(paddleSize);
    p1.setPosition(30.f, player1Y);

    sf::RectangleShape p2;
    p2.setSize(paddleSize);
    p2.setPosition(WINDOW_WIDTH - 30.f, player2Y);

    /* Ball setup */
    sf::RectangleShape ball;
    ball.setSize(ballSize);
    sf::Vector2f ballPos(((WINDOW_WIDTH / 2) - (ballSize.x / 2)), (WINDOW_HEIGHT / 2 - (ballSize.y / 2)));
    ball.setPosition(ballPos.x, ballPos.y);

    // a total mess, honestly
    // randInSomeRange = (rand() % (max-min + 1)) + min;
    float ballDX = (rand() % (2 - 1 + 1)) + 1 == 1 ? 300 : -300;
    float ballDY = (rand() % (150 + 150 + 1)) - 150;

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
    float smoothTimer;

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

                    // reset ball to starting position and speed
                    ballPos.x = ((WINDOW_WIDTH / 2) - (ballSize.x / 2));
                    ballPos.y =  (WINDOW_HEIGHT / 2 - (ballSize.y / 2));
                    ball.setPosition(ballPos.x, ballPos.y);

                    ballDX = (rand() % (2 - 1 + 1)) + 1 == 1 ? 300 : -300;
                    ballDY = (rand() % (150 + 150 + 1)) - 150;

                }
            }

        }

        // handle input
        // these silly long tertiary expressions mean I can now get rid of #include <algorithm>
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            player1Y = (0.f > player1Y - PADDLE_SPEED * dt.asSeconds() ? 0.f : player1Y - PADDLE_SPEED * dt.asSeconds());
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            player1Y = (WINDOW_HEIGHT - (paddleSize.y) < player1Y + PADDLE_SPEED * dt.asSeconds() ? WINDOW_HEIGHT - (paddleSize.y) : player1Y + PADDLE_SPEED * dt.asSeconds());
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            player2Y = (0.f > player2Y - PADDLE_SPEED * dt.asSeconds() ? 0.f : player2Y - PADDLE_SPEED * dt.asSeconds());
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            player2Y = (WINDOW_HEIGHT - (paddleSize.y) < player2Y + PADDLE_SPEED * dt.asSeconds() ? WINDOW_HEIGHT - (paddleSize.y) : player2Y + PADDLE_SPEED * dt.asSeconds());
        }

        /** Update **/
        p1.setPosition(30, player1Y);
        p2.setPosition(WINDOW_WIDTH - 30, player2Y);

        if (gameState == "play")
        {
            ballPos.x += ballDX * dt.asSeconds();
            ballPos.y += ballDY * dt.asSeconds();
        }

        ball.setPosition(ballPos.x, ballPos.y);

        /** Draw **/
        window.clear(color);
        window.draw(text);
        window.draw(p1scoreboard);
        window.draw(p2scoreboard);
        window.draw(p1);
        window.draw(p2);
        window.draw(ball);

        int fps = ceil(1.f / dt.asSeconds());
        smoothTimer += dt.asMilliseconds();

        if (smoothTimer > 500.f)
        {
            fpsCtr.setString("FPS: " + std::to_string(fps));
            smoothTimer = 0.f;
        }

        if (showDebug)
        {
            window.draw(fpsCtr);
        }

        window.display();

    }

    return 0;
}

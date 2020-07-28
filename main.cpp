/**
 *  Okay, so I got ahead of myself with the
 *  FPS counter, but it was fun. :D
 *
 */

#include <SFML/Graphics.hpp>
#include <math.h>               // needed for ceil()

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const int TEXT_SIZE = 24;
const int PADDLE_SPEED = 600;

int main()
{
    // window setup
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "pong-3");
    window.setFramerateLimit(60);

    // Declare and load our font
    sf::Font font;
    font.loadFromFile("font.ttf");

    // text setup gubbins
    sf::Text text("Hello, Pong!", font);
    text.setCharacterSize(TEXT_SIZE);
    // get a rect of the text so we can halve it for centering
    sf::FloatRect textBox = text.getGlobalBounds();
    text.setPosition((WINDOW_WIDTH / 2 - (textBox.width / 2)), 60);


    // window bg color
    sf::Color color(40, 45, 52);

    // default values
    sf::Vector2f paddleSize(15, 60);
    sf::Vector2f ballSize(12, 12);
    float player1Y = 90;
    float player2Y = WINDOW_HEIGHT - 150;

    // factor out yPos to variables for movement
    sf::RectangleShape p1;
    p1.setSize(paddleSize);
    p1.setPosition(30, player1Y);

    sf::RectangleShape p2;
    p2.setSize(paddleSize);
    p2.setPosition(WINDOW_WIDTH - 30, player2Y);

    sf::RectangleShape ball;
    ball.setSize(ballSize);
    ball.setPosition(((WINDOW_WIDTH / 2) - (ballSize.x / 2)), (WINDOW_HEIGHT / 2 - (ballSize.y / 2)));

    // score inits
    unsigned short player1score = 0;
    unsigned short player2score = 0;

    sf::Text p1scoreboard(std::to_string(player1score), font, 100);
    p1scoreboard.setPosition(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 3);
    sf::Text p2scoreboard(std::to_string(player2score), font, 100);
    p2scoreboard.setPosition(WINDOW_WIDTH / 2 + 90, WINDOW_HEIGHT / 3);

    // FPS counter stuff
    sf::Text fpsCtr("FPS:", font, 25);
    fpsCtr.setFillColor(sf::Color::Green);
    fpsCtr.setPosition(5.f, 5.f);

    bool showDebug = false;

    float smoothTimer;

    sf::Clock clock;

    // "game" loop, such as it is
    while (window.isOpen())
    {
        sf::Time dt = clock.restart();

        sf::Event event;
        while (window.pollEvent(event))

        {
            if ((event.type == sf::Event::Closed) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }

            if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F11))
            {
                showDebug = !showDebug;
            }

        }

        // handle input
        // TODO: MB: ok, so, originally i had this stuck inside the while-pollevent loop, and these were similar
        // sf::EventType::KeyPressed checks - it did some weird blocking call thing - one of the SFML books talked
        // about that and I didn't understand at the time - need to go back and read that so i grok it
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            player1Y = player1Y - PADDLE_SPEED * dt.asSeconds();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            player1Y = player1Y + PADDLE_SPEED * dt.asSeconds();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            player2Y -= PADDLE_SPEED * dt.asSeconds();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            player2Y += PADDLE_SPEED * dt.asSeconds();
        }

        // update
        p1.setPosition(30, player1Y);
        p2.setPosition(WINDOW_WIDTH - 30, player2Y);

        // draw
        window.clear(color);
        window.draw(text);
        window.draw(p1scoreboard);
        window.draw(p2scoreboard);
        window.draw(p1);
        window.draw(p2);
        window.draw(ball);

        // fps counter gubbins
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

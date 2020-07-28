#include <SFML/Graphics.hpp>

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const int TEXT_SIZE = 24;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "pong-2");

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

    sf::Vector2f paddleSize(15, 60);
    sf::Vector2f ballSize(12, 12);

    sf::RectangleShape p1;
    p1.setSize(paddleSize);
    p1.setPosition(30, 90);

    sf::RectangleShape p2;
    p2.setSize(paddleSize);
    p2.setPosition(WINDOW_WIDTH - 30 - paddleSize.x, WINDOW_HEIGHT - 150);

    sf::RectangleShape ball;
    ball.setSize(ballSize);
    ball.setPosition(((WINDOW_WIDTH / 2) - (ballSize.x / 2)), (WINDOW_HEIGHT / 2 - (ballSize.y / 2)));

    // "game" loop, such as it is
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if ((event.type == sf::Event::Closed) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
        }

        window.clear(color);

        window.draw(text);
        window.draw(p1);
        window.draw(p2);
        window.draw(ball);

        window.display();
    }

    return 0;
}

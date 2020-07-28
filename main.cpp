#include <SFML/Graphics.hpp>

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const int TEXT_SIZE = 20;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "pong-0");

    sf::Font font;
    font.loadFromFile("font.ttf");

    sf::Text text("\"The sky was the color of television, tuned to a dead channel.\"", font);
    text.setCharacterSize(TEXT_SIZE);
    sf::FloatRect textBox = text.getGlobalBounds();

    text.setPosition((WINDOW_WIDTH / 2 - (textBox.width / 2)), (WINDOW_HEIGHT / 2 - (TEXT_SIZE / 2)));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
        }

        window.clear();
        window.draw(text);
        window.display();
    }
    return 0;
}

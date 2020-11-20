#include <./SFML/Graphics.hpp>

int main()
{
    int size = 400;
    sf::RenderWindow window(sf::VideoMode(size, size), "SFML works!");
    sf::RectangleShape tower(sf::Vector2f(size * 4.0f/5, size * 4.0f/5));
    sf::Texture towerTexture;
    towerTexture.loadFromFile("textures/tower.png");
    tower.setTexture(&towerTexture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::TextEntered:
                    if (event.text.unicode < 128)
                        printf("%c", event.text.unicode);
                    break;
            }
        }

        window.clear(sf::Color::White);
        window.draw(tower);
        window.display();
    }

    return 0;
}
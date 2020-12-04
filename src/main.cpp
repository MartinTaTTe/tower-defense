#include <SFML/Graphics.hpp>
#include "game/app.hpp"
#include "utils/app_constants.hpp"

void test();

int main()
{
    App app;
    app.Run(WINDOW_WIDTH, WINDOW_HEIGHT);
    //test();
}

/*
Use the test function for easily testing small things.
Comment out line 9 and 10 in main and remove comment from
line 11.
Remember Ctrl+K+C to comment block of code and
Ctrl+K+U to uncomment block of code.
!!! DO NOT commit changes to main.cpp. !!!
*/
// Add your #include below, example:
// #include <iostream>

// -----------------------
void test() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Test Window");
    // Define your data types below, example:
    // sf::RectangleShape tower(sf::Vector2f(WINDOW_WIDTH * 4.0f/5, WINDOW_HEIGHT * 4.0f/5));
    // sf::Texture towerTexture;
    // towerTexture.loadFromFile(T_DEFAULT_TOWER);
    // tower.setTexture(&towerTexture);

    // --------------------------------------
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                // Test user input as case statements below, example:
                // case sf::Event::TextEntered:
                //     if (event.text.unicode < 128)
                //         printf("%c", event.text.unicode);
                //     break;

                // --------------------------------------------------
            }
        }
        window.clear(sf::Color::White);
        // Draw below, example:
        // window.draw(tower);

        // --------------------
        window.display();
    }
}

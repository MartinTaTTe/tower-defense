#include "app.hpp"

App::App(int height, int width) {
    sf::RenderWindow window(sf::VideoMode(height, width), "Tower Defense");
}
#include <iostream>
App::~App() {
    
}

void App::Run() {

    std::string str;
    std::getline(std::cin, str);
}


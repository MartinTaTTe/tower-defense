#include "app.hpp"

#include <chrono>
#include <future>
#include <iostream>

App::App(int height, int width)
    : height_(height), width_(width) {
    PushState(new MenuState());
}
App::~App() {
    for (auto state : states_) {
      delete state;
    }
}

void App::PushState(State* state) {
    states_.push_back(state);
    std::cout << "Switch to " << state->GetName() << std::endl;
}

void App::PopState() {
    if (!states_.empty()) {
        delete states_.back();
        states_.pop_back();
    }
}

void App::Run() {
    sf::RenderWindow window(sf::VideoMode(width_, height_), "Tower Defense");
    
    auto start = std::chrono::high_resolution_clock::now();
    while (window.isOpen()) {
        sf::Event event;
        State* state = states_.back()->EventHandler(window, event);
        if (states_.back() != state)
            PushState(state);
        window.clear(sf::Color::White);
        states_.back()->Draw(window);
        window.display();
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;
    std::cout << "Exited successfully. App was running for " << duration.count() << " seconds." << std::endl;
}


#include "app.hpp"
#include "../utils/app_constants.hpp"
#include "../utils/event.hpp"

#include <chrono>
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
    sf::RenderWindow window(sf::VideoMode(width_, height_), WINDOW_TITLE);
    
    auto start = std::chrono::high_resolution_clock::now();

    while (window.isOpen()) {
        sf::Event sf_event;
        while (window.pollEvent(sf_event)) {
            if (sf_event.type == sf::Event::Closed) {
                window.close();
            } else {
                Event event = states_.back()->EventHandler(sf_event);
                switch(event.type) {
                    case EventType::None:
                        break;
                    case EventType::PopState:
                        PopState();
                        break;
                    case EventType::PushState:
                        PushState(event.state);
                        sf_event.type = sf::Event::Closed;
                        sf_event.size.width = window.getSize().x;
                        sf_event.size.height = window.getSize().y;
                        states_.back()->EventHandler(sf_event);
                        break;
                }
            }
        }
        window.clear(sf::Color(BACKGROUND_R, BACKGROUND_G, BACKGROUND_B));
        states_.back()->Draw(window);
        window.display();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;

    std::cout << "Exited successfully. App was running for " << duration.count() << " seconds." << std::endl;
}

#include "app.hpp"
#include "../utils/app_constants.hpp"
#include "../utils/event.hpp"
#include "game_state.hpp"

#include <chrono>
#include <iostream>

App::App() {

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

void App::Run(int width, int height) {
    auto start = std::chrono::high_resolution_clock::now();

    sf::RenderWindow window(sf::VideoMode(width, height), WINDOW_TITLE);
    PushState(new MenuState(width, height));

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
                    case EventType::PushGameState:
                        PushState(new GameState(width, height, M_BASIC_MAP));
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

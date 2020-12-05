
#include "app.hpp"
#include "../utils/app_constants.hpp"
#include "../utils/event.hpp"
#include "menu_state.hpp"
#include "game_state.hpp"
#include "input_state.hpp"
#include "mapeditor_state.hpp"

#include <chrono>
#include <iostream>
#include <windows.h>

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
        std::cout << "Switch to " << states_.back()->GetName() << std::endl;
    }
}

void App::Run(int width, int height) {
    auto start = std::chrono::high_resolution_clock::now();

    sf::RenderWindow window(sf::VideoMode(width, height), WINDOW_TITLE);
    PushState(new MenuState(width, height));
    auto last_frame = start;
    auto this_frame = std::chrono::high_resolution_clock::now();
    
    while (window.isOpen()) {
        last_frame = this_frame;
        this_frame = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> frame = this_frame - last_frame;
        double frame_duration = frame.count();
        
        sf::Event sf_event;
        window.pollEvent(sf_event);

        if (sf_event.type == sf::Event::Closed) {
            window.close();
        } else {
            Event event = states_.back()->EventHandler(frame_duration, sf_event);
            switch(event.type) {
                case EventType::None:
                    break;
                case EventType::PopState:
                    PopState();
                    break;
                case EventType::PushGameState:
                    PushState(new GameState(width, height, M_BASIC_MAP));
                    break;
                case EventType::PushInputState:
                    PushState(new InputState(width, height));
                    break;
                case EventType::PushMapEditorState:
                    PushState(new MapEditorState(width, height, event.increments.x, event.increments.y));
                    break;
            }
        }
        
        window.clear(sf::Color(BACKGROUND_R, BACKGROUND_G, BACKGROUND_B));
        states_.back()->Draw(window);
        window.display();
        Sleep(10);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;
    std::cout << "Exited successfully. App was running for " << duration.count() << " seconds." << std::endl;
}

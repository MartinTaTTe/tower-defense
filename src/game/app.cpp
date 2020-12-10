
#include "app.hpp"
#include "../utils/app_constants.hpp"
#include "../utils/event.hpp"
#include "menu_state.hpp"
#include "game_state.hpp"
#include "input_state.hpp"
#include "mapeditor_state.hpp"
#include "mapselect_state.hpp"

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
        std::cout << "Switch to " << states_.back()->GetName() << std::endl;
    }
}

void App::Run(int width, int height) {
    auto start = std::chrono::high_resolution_clock::now();

    sf::RenderWindow window(sf::VideoMode(width, height), WINDOW_TITLE);
    window.setFramerateLimit(60);
    PushState(new MenuState(width, height));
    auto last_frame = start;
    auto this_frame = std::chrono::high_resolution_clock::now();
    
    while (window.isOpen()) {
        last_frame = this_frame;
        this_frame = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> frame = this_frame - last_frame;
        double frame_duration = frame.count();
        
        sf::Event sf_event;
        sf_event.type = sf::Event::Count;
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
                    sf_event.size.width  = window.getSize().x;
                    sf_event.size.height = window.getSize().y;
                    sf_event.type = sf::Event::Resized;
                    states_.back()->EventHandler(0, sf_event);
                    break;
                case EventType::PushGameState:
                    PushState(new GameState(window.getSize().x, window.getSize().y, MAPS[event.x], WAVES[event.x]));
                    break;
                case EventType::PushInputState:
                    PushState(new InputState(window.getSize().x, window.getSize().y));
                    break;
                case EventType::PushMapEditorState:
                    PushState(new MapEditorState(window.getSize().x, window.getSize().y, event.increments.x, event.increments.y));
                    break;
                case EventType::PushMapSelectState:
                    PushState(new MapSelectState(window.getSize().x, window.getSize().y));
                    break;
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

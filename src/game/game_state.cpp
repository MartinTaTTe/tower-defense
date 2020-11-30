#include "game_state.hpp"

GameState::GameState(Map* map)
    : map_(map), State("Game State") { }

State* GameState::EventHandler(sf::RenderWindow& window, sf::Event& event) {
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
        }
    }
    return this;
}

void GameState::Draw(sf::RenderWindow& window) {
    map_->Draw(window);
}

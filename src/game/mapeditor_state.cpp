#include "mapeditor_state.hpp"
#include <iostream>
#include <fstream>

MapEditorState::MapEditorState(const Vector2i& size, const int& width, const int& height, const std::string& name)
    : map_(new Map({0, 0, MAP_WIDTH * size.x, (float)size.y}, width, height)), name_(name), width_(width), height_(height), State("MapEditor State") { }

Event MapEditorState::EventHandler(const sf::Event& sf_event) {
        Event event(EventType::None);
        switch (sf_event.type) {
            case sf::Event::MouseMoved:
                event.type = EventType::MouseMovement;
                event.coords.x = sf_event.mouseMove.x;
                event.coords.y = sf_event.mouseMove.y;
                map_->EventHandler(event);
                break;
            case sf::Event::MouseButtonPressed:
                event.type = EventType::MouseClick;
                event.coords.x = sf_event.mouseButton.x;
                event.coords.y = sf_event.mouseButton.y;
                map_->EventHandler(event);
                break;
            case sf::Event::Resized:
                event.type = EventType::Resize;
                map_->EventHandler(event);
                break;
            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    Save();
                }
                break;
        }
    return event;
}

void MapEditorState::Save() {
    std::string fileName = name_ + ".txt";
    std::ofstream file;
    
    file.open(fileName);
    file << width_ + "x" + height_ << std::endl;
    
    for(int y = 0; y < height_; y++) {
        for(int x = 0; x < width_; x++) {
            Tile* tile = map_->GetTile(x, y);
            file << (int)(tile->GetType());
        }
        file << std::endl;
    }
    std::cout << "kys" << std::endl;
    file.close();

}

void MapEditorState::Draw(sf::RenderWindow& window) {
    map_->Draw(window);
}
#include "mapeditor_state.hpp"
#include "../utils/app_constants.hpp"
#include "../utils/texture_manager.hpp"
#include <windows.h>
#include <iostream>
#include <fstream>

MapEditorState::MapEditorState(int width, int height, int grid_width, int grid_height)
    : State("Map Editor State", width, height), grid_width_(grid_width), grid_height_(grid_height) {
    AddBlankMap({0, 0, 0.8f, 1}, grid_width, grid_height);
    AddCanvas({0.8f, 0, 1, 1}); // siderbar
    canvases_.back().second->AddButton({0, 0.8f, 1, 1}, T_RETURN_TO_MENU, Event(EventType::PopState)); // return to menu
    Event event(EventType::SelectTile);
    event.tileType = TileType::Path;
    canvases_.back().second->AddButton({0, 0, 1, 0.2f}, T_TILES[0], event);
    event.tileType = TileType::Grass;
    canvases_.back().second->AddButton({0, 0.2f, 1, 0.4f}, T_TILES[1], event);
    event.tileType = TileType::Water;
    canvases_.back().second->AddButton({0, 0.4f, 1, 0.6f}, T_TILES[2], event);
    canvases_.back().second->AddButton({0, 0.6f, 1, 0.8f}, T_DEFAULT_BUTTON, Event(EventType::Save));
    canvases_[0].second->AddText({0, 0}, "0 FPS", 30); // FPS counter
}

Event MapEditorState::EventHandler(double d_time, const sf::Event& sf_event) {
    Event event;
    canvases_[0].second->UpdateString(0, std::to_string((int)(1.0 / d_time)) + " FPS");
    switch (sf_event.type) {
        case sf::Event::Resized:
            OnResize(sf_event.size.width, sf_event.size.height);
            break;
        case sf::Event::MouseMoved:
            OnMouseMovement(sf_event.mouseMove.x, sf_event.mouseMove.y);
            break;
        case sf::Event::MouseButtonPressed:
            event = OnClick(sf_event.mouseButton.x, sf_event.mouseButton.y);
            event = CustomMouseClick(event);
            
            break;
        case sf::Event::MouseButtonReleased:
            event.type = EventType::MouseClickReleased;
            event.coords.x = sf_event.mouseButton.x;
            event.coords.y = sf_event.mouseButton.y;
            event = CustomMouseRelease(event);
            
        default:
            break;
    }
    
    return event;
}

Event MapEditorState::CustomMouseClick(Event event) {
    Event return_event;
    switch (event.type) {
        case EventType::SelectTile:
            selectedTile = event.tileType;
            break;
        case EventType::PopState:
            return_event.type = EventType::PopState;
            break;
        case EventType::Save:
            //Sleep(1000);
            return_event = Save();
            break;
        default:
            break;
    }
    return return_event;
}

Event MapEditorState::CustomMouseRelease(Event event) {
    Event return_event;
    switch (event.type) {
        case EventType::MouseClickReleased:
            Map* map = dynamic_cast<Map*>(canvases_[0].second);
            if (event.coords.x < width_*0.8f) {
                map->UpdateTile((event.coords.x*grid_width_)/(width_*0.8f), (event.coords.y*grid_height_/height_), selectedTile);
            }
            break;
    }
}

Event MapEditorState::Save() {
    std::string fileName = "map/maps/jeff.map";
    std::fstream mapFile;
    Map* map = dynamic_cast<Map*>(canvases_[0].second);
    mapFile.open("jeff.map");
    if (mapFile.is_open()) {
        mapFile << grid_width_ << "x" << grid_height_ << std::endl;
    for(int y = 0; y < grid_height_; y++) {
        for(int x = 0; x < grid_width_; x++) {
            Tile* tile = map->GetTile(x, y);
            mapFile << (int)(tile->GetType());
        }
        mapFile << std::endl;
    }
    mapFile.close();
    }
    return Event(EventType::PopState);
}
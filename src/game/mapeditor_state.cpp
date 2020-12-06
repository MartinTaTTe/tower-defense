#include "mapeditor_state.hpp"
#include "../utils/app_constants.hpp"
#include "../utils/texture_manager.hpp"
#include <iostream>
#include <fstream>

MapEditorState::MapEditorState(int width, int height, int grid_width, int grid_height)
    : State("Map Editor State", width, height), grid_width_(grid_width), grid_height_(grid_height) {
    AddCanvas({0, 0, 0.8f, 1}, grid_width, grid_height);
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

void MapEditorState::Update(double d_time) {
    canvases_[0].second->UpdateString(0, std::to_string((int)(1.0 / d_time)) + " FPS");
}

Event MapEditorState::CustomOnClick(Event event) {
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
        case EventType::MouseClickReleased:
            if (event.coords.x < width_*0.8f) {
                Map* map = dynamic_cast<Map*>(canvases_[0].second);
                map->UpdateTile((event.coords.x*grid_width_)/(width_*0.8f), (event.coords.y*grid_height_/height_), selectedTile);
            }
            break;
        default:
            break;
    }
    return return_event;
}

Event MapEditorState::Save() {
    std::ofstream mapFile;
    Map* map = dynamic_cast<Map*>(canvases_[0].second);
    mapFile.open(MAPS[1]);
    if (mapFile.is_open()) {
        mapFile << grid_width_ << "x" << grid_height_ << std::endl;
        mapFile << "start" << std::endl;
        mapFile << "end" << std::endl;
        for (int y = 0; y < grid_height_; y++) {
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

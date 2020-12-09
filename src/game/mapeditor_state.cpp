#include "mapeditor_state.hpp"
#include "../utils/app_constants.hpp"
#include "../utils/texture_manager.hpp"
#include "../utils/path_finder.hpp"
#include <iostream>
#include <fstream>

MapEditorState::MapEditorState(int width, int height, int grid_width, int grid_height)
    : State("Map Editor State", width, height), grid_width_(grid_width), grid_height_(grid_height), start_({0,0}), end_({grid_width,grid_height}), start_selected(false), end_selected(false), errorMessage_(false) {
    AddCanvas({0, 0, 0.8f, 1}, grid_width, grid_height);
    AddCanvas({0.8f, 0, 1, 1}); // siderbar
    canvases_.back().second->AddButton({0, 0.9f, 1, 1}, T_RETURN_TO_MENU_BUTTON, Event(EventType::PopState)); // return to menu
    Event event(EventType::SelectTile);
    event.tileType = TileType::Path;
    canvases_.back().second->AddButton({0, 0, 1, 0.15f}, T_TILES[0], event);
    event.tileType = TileType::Grass;
    canvases_.back().second->AddButton({0, 0.15f, 1, 0.3f}, T_TILES[1], event);
    event.tileType = TileType::Water;
    canvases_.back().second->AddButton({0, 0.3f, 1, 0.45f}, T_TILES[2], event);
    canvases_.back().second->AddButton({0, 0.45f, 1, 0.6f}, T_SELECT_START_BUTTON, Event(EventType::Start));
    canvases_.back().second->AddButton({0, 0.6f, 1, 0.75f}, T_SELECT_END_BUTTON, Event(EventType::End));
    canvases_.back().second->AddButton({0, 0.75f, 1, 0.9f}, T_SAVE_BUTTON, Event(EventType::Save));
}

void MapEditorState::Update(double d_time) {
    counter_ += d_time;
    if (counter_ > 3 && errorMessage_) {
        delete canvases_.back().second;
        canvases_.pop_back();
        counter_ = 0;
        errorMessage_ = false;
    }
}

Event MapEditorState::CustomOnClick(Event event) {
    Event return_event;
    Map* map = dynamic_cast<Map*>(canvases_[0].second);
    switch (event.type) {
        case EventType::SelectTile:
            selectedTile = event.tileType;
            start_selected = false;
            end_selected = false;
            break;
        case EventType::PopState:
            return_event.type = EventType::PopState;
            break;
        case EventType::Save:
            return_event = Save();
            break;
        case EventType::MouseClickReleased:
            if (event.body.upper_left_x < MAP_WIDTH && start_selected) {
                event = map->UpdateTile(event, selectedTile, true);
                if (event.x != -1)
                    start_ = event.increments;
            } else if (event.body.upper_left_x < MAP_WIDTH && end_selected) {
                event = map->UpdateTile(event, selectedTile, true);
                if (event.x != -1) {
                    end_ = event.increments;
                }
            } else if (event.body.upper_left_x < MAP_WIDTH) {
                map->UpdateTile(event, selectedTile, false);
            }
            break;
        case EventType::Start:
            start_selected = true;
            end_selected = false;
            break;
        case EventType::End:
            end_selected = true;
            start_selected = false;
            break;
        default:
            break;
    }
    return return_event;
}

Event MapEditorState::Save() {
    std::ofstream mapFile;
    Map* map = dynamic_cast<Map*>(canvases_[0].second);
    mapFile.open(MAPS[0]);
    if (mapFile.is_open()) {
        mapFile << grid_width_ << "x" << grid_height_ << std::endl;
        mapFile << start_.x << "," << start_.y << std::endl;
        mapFile << end_.x << "," << end_.y << std::endl;
        for (int y = 0; y < grid_height_; y++) {
            for(int x = 0; x < grid_width_; x++) {
                Tile* tile = map->GetTile(x, y);
                mapFile << (int)(tile->type);
            }
            mapFile << std::endl;
        }
        mapFile.close();
    }
    PathFinder finder(MAPS[0]);
    if (finder.findPath()) {
        return Event(EventType::PopState);
    } else {
        AddCanvas({0,0,1,1});
        canvases_.back().second->AddText({0,0.5f}, "A complete path was not found. \n Please make a viable path with start and end.", 30, sf::Color::Red);
        errorMessage_ = true;
        counter_ = 0;
    }
    return Event(EventType::None);
}

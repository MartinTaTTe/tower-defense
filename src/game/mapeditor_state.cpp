#include "mapeditor_state.hpp"
#include "../utils/app_constants.hpp"
#include "../utils/texture_manager.hpp"
#include "../utils/path_finder.hpp"
#include <iostream>
#include <fstream>

MapEditorState::MapEditorState(int width, int height, int grid_width, int grid_height)
    : State("Map Editor State", width, height), grid_width_(grid_width), grid_height_(grid_height), start_({0,0}), end_({grid_width,grid_height}), start_selected(false), end_selected(false) {
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
            start_selected = false;
            end_selected = false;
            break;
        case EventType::PopState:
            return_event.type = EventType::PopState;
            break;
        case EventType::Save:
            //Sleep(1000);
            return_event = Save();
            break;
        case EventType::MouseClickReleased:
            if (event.coords.x < width_*0.8f && start_selected) {
                Map* map = dynamic_cast<Map*>(canvases_[0].second);
                Tile* tile = map->GetTile((int)((event.coords.x*grid_width_)/(width_*0.8f)), (int)(event.coords.y*grid_height_/height_));
                if (tile->GetType() == TileType::Path) {
                    start_ = Vector2i({(int)((event.coords.x*grid_width_)/(width_*0.8f)), (int)(event.coords.y*grid_height_/height_)});
                    map->UpdateTile(start_.x, start_.y, selectedTile, true);
                }
            } else if (event.coords.x < width_*0.8f && end_selected) {
                Map* map = dynamic_cast<Map*>(canvases_[0].second);
                Tile* tile = map->GetTile((int)((event.coords.x*grid_width_)/(width_*0.8f)), (int)(event.coords.y*grid_height_/height_));
                if (tile->GetType() == TileType::Path) {
                    end_ = Vector2i({(int)((event.coords.x*grid_width_)/(width_*0.8f)), (int)(event.coords.y*grid_height_/height_)});
                    map->UpdateTile(end_.x, end_.y, selectedTile, true);
                }
            } else if (event.coords.x < width_*0.8f) {
                Map* map = dynamic_cast<Map*>(canvases_[0].second);
                map->UpdateTile((event.coords.x*grid_width_)/(width_*0.8f), (event.coords.y*grid_height_/height_), selectedTile, false);
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
    mapFile.open(MAPS[1]);
    if (mapFile.is_open()) {
        mapFile << grid_width_ << "x" << grid_height_ << std::endl;
        mapFile << start_.x << "," << start_.y << std::endl;
        mapFile << end_.x << "," << end_.y << std::endl;
        for (int y = 0; y < grid_height_; y++) {
            for(int x = 0; x < grid_width_; x++) {
                Tile* tile = map->GetTile(x, y);
                mapFile << (int)(tile->GetType());
            }
            mapFile << std::endl;
        }
        mapFile.close();
    }
    Path_Finder finder(MAPS[1]);
    if (finder.findPath()) {
        return Event(EventType::PopState);
    } 
    return Event(EventType::None);
}

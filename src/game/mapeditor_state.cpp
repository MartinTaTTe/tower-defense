#include "mapeditor_state.hpp"
#include <iostream>
#include <fstream>

// MapEditorState::MapEditorState(const Vector2i& size, const int& width, const int& height, const std::string& name)
//     : map_(new Map({0, 0, MAP_WIDTH * size.x, (float)size.y}, width, height)), name_(name), width_(width), height_(height), State("MapEditor State") { }



// void MapEditorState::Save() {
//     std::string fileName = "map/maps/" + name_ + ".map";
//     std::ofstream file;
    
//     file.open(fileName);
//     file << width_ << "x" << height_ << std::endl;
    
//     for(int y = 0; y < height_; y++) {
//         for(int x = 0; x < width_; x++) {
//             Tile* tile = map_->GetTile(x, y);
//             file << (int)(tile->GetType());
//         }
//         file << std::endl;
//     }
//     file.close();

// }

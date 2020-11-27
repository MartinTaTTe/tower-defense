#include "map.hpp" 

Map::Map(int height, int width) 
    : height_(height), width_(width) {     
    for (int i = 0; i < height; i++) {
        tiles_.push_back(std::vector<Tile*>());
        for (int j = 0; j < width; j++) {
            tiles_[i].push_back(new Tile((TileTypes)(rand() % 3)));
        }
    }
}

Tile* Map::GetTile(int x, int y) const {
    return tiles_[y][x];
}

void Map::Draw(sf::RenderWindow& window) {
  auto windowsize = window.getSize();
  int tile_size_x = (windowsize.x) / width_;
  int tile_size_y = (windowsize.y) / height_;
  auto tile_size = std::min(tile_size_x, tile_size_y);
  for (int y = 0; y < height_; y++) {
    for (int x = 0; x < width_; x++) {
      Tile* tile = tiles_[y][x];
      tile->SetPos(x * tile_size, y * tile_size);
      tile->SetScale(tile_size);
      tile->draw(window);
    }
  }
}




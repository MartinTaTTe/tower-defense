#include "map.hpp" 

Map::Map(int height, int width) 
    : height_(height), width_(width) {   
    for (int i = 0; i < height; i++) {
        tiles_.push_back(std::vector<Tile*>());
        for (int j = 0; j < width; j++) {
            tiles_[i].push_back(new Tile((TileType)(rand() % 3)));
        }
    }
}

Map::Map(const std::string& filePath) {
  std::ifstream file(filePath);
  std::string line;
  int y = 0;
  while(std::getline(file,line)) {
    tiles_.push_back(std::vector<Tile*>());
    width_ = line.length();
    for (auto i : line) {
      switch(i) {
        case '0':
          tiles_[y].push_back(new Tile(Grass));
          break;
        case '!':
          tiles_[y].push_back(new Tile(Water));
          break;
        case '#':
          tiles_[y].push_back(new Tile(Path));
          break;
        default:
          tiles_[y].push_back(new Tile(Grass));
          break;
      }
    }
    y++;
  }
  height_ = y;
}

Map::~Map() {
  for (auto column : tiles_) {
    for (auto tile : column) {
      delete tile;
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
  int tile_size = std::min(tile_size_x, tile_size_y);
  for (int y = 0; y < height_; y++) {
    for (int x = 0; x < width_; x++) {
      Tile* tile = tiles_[y][x];
      tile->SetPosition(x * tile_size, y * tile_size);
      tile->SetSize(tile_size_x, tile_size_y);
      tile->Draw(window);
    }
  }
}




#pragma once
/*
This file contains all values that are used for balancing purposes and won't break functionality if changed.
*/
// App constants
const std::string WINDOW_TITLE = "Tower Defense";
const int WINDOW_HEIGHT = 500;
const int WINDOW_WIDTH  = 1000;
const int HIGHLIGHT = 100; // 0-255
const int DISABLE   = 100; // 0-255
const int BACKGROUND_R = 200;
const int BACKGROUND_G = 200;
const int BACKGROUND_B = 200;
const float MAP_WIDTH = 0.8f; // 0-1

// Tower constants
const int UPGRADE_PRICE = 1000;

// Enemy constants


// Texture paths, name like "T_NAME_OF_TEXTURE"
const std::string T_DEFAULT_BUTTON = "textures/default_button.png";
const std::string T_TILES[] = {
    "textures/path.png",
    "textures/grass.png",
    "textures/water.png"
};
const std::string T_DEFAULT_TOWER = "textures/tower.png";
const std::string T_UTILITY_TOWER = "textures/utility_tower.png";

// Map paths, name like "M_NAME_OF_MAP"
const std::string M_BASIC_MAP = "map/maps/basic.map";

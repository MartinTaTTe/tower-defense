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
const float MAP_HEIGHT = 1.0f; // 0-1
const std::string DEFAULT_FONT = "utils/OpenSans.ttf";
const double SPAWN_SPEED = 0.4;
const int PLAYER_LIVES = 10;
const float HP_BAR_THICC = 0.1f;
const int START_GOLD = 300;
const int WAVE_GOLD = 150;

// Map paths
const std::string MAPS[] = {
    "map/maps/user.map",
    "map/maps/easy.map",
    "map/maps/medium.map",
    "map/maps/hard.map",
    "map/maps/basic.map"
};

// Wave paths
const std::string WAVES[] = {
    "enemies/waves/basic.wave",
    "enemies/waves/easy.wave",
    "enemies/waves/medium.wave",
    "enemies/waves/hard.wave",
    "enemies/waves/basic.wave"
};

// Tower constants

const float BASIC_TOWER_DAMAGE = 10;
const float BASIC_TOWER_RANGE = 6;
const int BASIC_TOWER_PRICE = 100;

const float FLYING_TOWER_DAMAGE = 20;
const float FLYING_TOWER_RANGE = 7;
const int FLYING_TOWER_PRICE = 100;

const float UTILITY_TOWER_DAMAGE = 5;
const float UTILITY_TOWER_RANGE = 0;
const int UTILITY_TOWER_PRICE = 400;

const float WATER_TOWER_DAMAGE = 25;
const float WATER_TOWER_RANGE = 5;
const int WATER_TOWER_PRICE = 300;

const float HYBRID_TOWER_DAMAGE = 20;
const float HYBRID_TOWER_RANGE = 6;
const int HYBRID_TOWER_PRICE = 500;

const float MULTIPLE_TOWER_DAMAGE = 10;
const float MULTIPLE_TOWER_RANGE = 4;
const int MULTIPLE_TOWER_PRICE = 500;

// Enemy constants
const float NORMAL_ENEMY_MAX_HP = 100.0f;
const float NORMAL_ENEMY_SPEED = 0.8f;
const int NORMAL_ENEMY_VALUE = 10;

const float FAST_ENEMY_MAX_HP = 75.0f;
const float FAST_ENEMY_SPEED = 1.2f;
const int FAST_ENEMY_VALUE = 15;

const float FLYING_ENEMY_MAX_HP = 150.0f;
const float FLYING_ENEMY_SPEED = 1;
const int FLYING_ENEMY_VALUE = 50;

const float REGEN_ENEMY_MAX_HP = 300.0f;
const float REGEN_ENEMY_SPEED = 0.25f;
const int REGEN_ENEMY_VALUE = 80;
const float REGEN_ENEMY_HPREGEN = 0.07f;

const float SPAWN_ENEMY_MAX_HP = 1000.0f;
const float SPAWN_ENEMY_SPEED = 0.3f;
const int SPAWN_ENEMY_VALUE = 100;

// Texture paths, name like "T_NAME_OF_TEXTURE"
// knappar
const std::string T_DEFAULT_BUTTON = "textures/buttons/default_button.png";
const std::string T_PLAY_BUTTON = "textures/buttons/Play_button.png";
const std::string T_RETURN_TO_MENU_BUTTON = "textures/buttons/Back_to_menu_button.png";
const std::string T_PLUS_BUTTON = "textures/buttons/Plus_button.png";
const std::string T_MINUS_BUTTON = "textures/buttons/Minus_button.png";
const std::string T_SAVE_BUTTON = "textures/buttons/Save_button.png";
const std::string T_MAP_EDITOR_BUTTON = "textures/buttons/Map_editor_button.png";
const std::string T_CUSTOM_MODE_BUTTON = "textures/buttons/Custom_mode_button.png";
const std::string T_SELECT_START_BUTTON = "textures/buttons/Select_start_button.png";
const std::string T_SELECT_END_BUTTON = "textures/buttons/Select_end_button.png";
const std::string T_PLAY_PAUSE_BUTTON = "textures/buttons/play_pause_button.png";
const std::string T_NEXT_WAVE_BUTTON = "textures/buttons/next_wave_button.png";

const std::string T_EASY_MAP = "textures/maps/easy.png";
const std::string T_MEDIUM_MAP = "textures/maps/medium.png";
const std::string T_HARD_MAP = "textures/maps/hard.png";
const std::string T_BASIC_MAP = "textures/maps/basic.png";

// 
const std::string T_HP_BAR = "textures/hp_bar.png";
const std::string T_DEFAULT_ENEMY = "textures/enemies/zombie.png";
const std::string T_FLYING_ENEMY = "textures/enemies/ufo.png";
const std::string T_FAST_ENEMY = "textures/enemies/ghost.png";
const std::string T_REGEN_ENEMY = "textures/enemies/sorcerer.png";
const std::string T_SPAWN_ENEMY = "textures/enemies/demon.png";
const std::string T_TILES[] = {
    "textures/path.png",
    "textures/grass.png",
    "textures/water.png"
};
const std::string T_DEFAULT_TOWER = "textures/tower.png";
const std::string T_UTILITY_TOWER = "textures/towers/bank.png";
const std::string T_BASIC_TOWER = "textures/towers/tower.png";
const std::string T_FLYING_TOWER = "textures/towers/balloon.png";
const std::string T_WATER_TOWER = "textures/towers/ship.png";
const std::string T_HYBRID_TOWER = "textures/towers/hybrid_tower.png";
const std::string T_MULTIPLE_TOWER = "textures/towers/multiple_tower.png";


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
const double SPAWN_SPEED = 1.0;
const int PLAYER_LIVES = 10;
const float HP_BAR_THICC = 0.1f;
const int START_GOLD = 5000;

// Map paths
const std::string MAPS[] = {
    "map/maps/basic.map",
    "map/maps/user.map"
};

// Waves paths, name like "W_NAME_OF_WAVES"
const std::string W_BASIC_WAVES = "enemies/waves/basic.wave";

// Tower constants
const int UPGRADE_PRICE = 1000;
const int UPGRADE_MAX = 3;

const float BASIC_TOWER_DAMAGE = 3.0f;
const float BASIC_TOWER_SPEED = 3;
const float BASIC_TOWER_RANGE = 3;
const int BASIC_TOWER_ENEMYTYPE = 1; 
const int BASIC_TOWER_PRICE = 100; 
const int BASIC_TOWER_TILETYPE = true; 

const float FLYING_TOWER_DAMAGE = 3;
const float FLYING_TOWER_SPEED = 3;
const float FLYING_TOWER_RANGE = 3;
const int FLYING_TOWER_ENEMYTYPE = 2; 
const int FLYING_TOWER_PRICE = 1000; 
const int FLYING_TOWER_TILETYPE = true; 

const float UTILITY_TOWER_DAMAGE = 1; 
const float UTILITY_TOWER_SPEED = 3;
const float UTILITY_TOWER_RANGE = 3;
const int UTILITY_TOWER_ENEMYTYPE = 2; 
const int UTILITY_TOWER_PRICE = 1000; 
const int UTILITY_TOWER_TILETYPE = true; 

const float WATER_TOWER_DAMAGE = 3; 
const float WATER_TOWER_SPEED = 3;
const float WATER_TOWER_RANGE = 3;
const int WATER_TOWER_ENEMYTYPE = 2; 
const int WATER_TOWER_PRICE = 1000; 
const int WATER_TOWER_TILETYPE = false; 

const float HYBRID_TOWER_DAMAGE = 3; 
const float HYBRID_TOWER_SPEED = 3;
const float HYBRID_TOWER_RANGE = 3;
const int HYBRID_TOWER_ENEMYTYPE = 3; 
const int HYBRID_TOWER_PRICE = 1000; 
const int HYBRID_TOWER_TILETYPE = true; 

const float MULTIPLE_TOWER_DAMAGE = 3; 
const float MULTIPLE_TOWER_SPEED = 3;
const float MULTIPLE_TOWER_RANGE = 3;
const int MULTIPLE_TOWER_ENEMYTYPE = 3; 
const int MULTIPLE_TOWER_PRICE = 1000; 
const int MULTIPLE_TOWER_TILETYPE = true;

// Enemy constants
const float NORMAL_ENEMY_MAX_HP = 100.0f;
const float NORMAL_ENEMY_SPEED = 0.5f;
const int NORMAL_ENEMY_VALUE = 10;

const float FAST_ENEMY_MAX_HP = 75.0f;
const float FAST_ENEMY_SPEED = 15.0f;
const int FAST_ENEMY_VALUE = 15;

const float FLYING_ENEMY_MAX_HP = 250.0f;
const float FLYING_ENEMY_SPEED = 5.0f;
const int FLYING_ENEMY_VALUE = 50;

const float REGEN_ENEMY_MAX_HP = 100.0f;
const float REGEN_ENEMY_SPEED = 10.0f;
const int REGEN_ENEMY_VALUE = 80;

const float SPAWN_ENEMY_MAX_HP = 100.0f;
const float SPAWN_ENEMY_SPEED = 10.0f;
const int SPAWN_ENEMY_VALUE = 15;

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

// 
const std::string T_HP_BAR = "textures/hp_bar.png";
const std::string T_DEFAULT_ENEMY = "textures/enemy.png";
const std::string T_FLYING_ENEMY = "textures/flying_enemy.png";
const std::string T_FAST_ENEMY = "textures/fast_enemy.png";
const std::string T_REGEN_ENEMY = "textures/regen_enemy.png";
const std::string T_SPAWN_ENEMY = "textures/spawn_enemy.png";
const std::string T_TILES[] = {
    "textures/path.png",
    "textures/grass.png",
    "textures/water.png"
};
const std::string T_DEFAULT_TOWER = "textures/tower.png";
const std::string T_UTILITY_TOWER = "textures/utility_tower.png";
const std::string T_BASIC_TOWER = "textures/basic_tower.png";
const std::string T_FLYING_TOWER = "textures/flying_tower.png";
const std::string T_WATER_TOWER = "textures/water_tower.png";
const std::string T_HYBRID_TOWER = "textures/hybrid_tower.png";
const std::string T_MULTIPLE_TOWER = "textures/multiple_tower.png";


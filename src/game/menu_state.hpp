#pragma once
/*
MenuState is the main menu, the first State a user sees.
*/
#include "state.hpp"

class MenuState : public State {
public:
    MenuState(int width, int height);
};

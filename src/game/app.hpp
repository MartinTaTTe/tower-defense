#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "state.hpp"
#include "menu_state.hpp"
#include "game_state.hpp"

class App {
public:
    App(int height, int width);
    ~App();
    void                PushState(State*);
    void                PopState();
    void                Run();
private:
    int                 height_;
    int                 width_;
    std::vector<State*> states_;
};



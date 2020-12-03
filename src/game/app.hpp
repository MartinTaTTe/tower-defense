#pragma once
/*
App manages the whole program through States. The most recently added State is the current State.
*/
#include <vector>

#include "menu_state.hpp"

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

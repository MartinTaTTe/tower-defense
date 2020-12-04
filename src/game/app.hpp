#pragma once
/*
App manages the whole program through States. The most recently added State is the current State.
*/
#include <vector>

#include "state.hpp"

class App {
public:
    App();
    ~App();
    void                PushState(State*);
    void                PopState();
    void                Run(int height, int width);
private:
    std::vector<State*> states_;
};

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "state.hpp"

class App {
public:
    App(int height, int width);
    ~App();
    void                PushState(State*);
    void                PopState();
    void                Run();
private:
    std::vector<State*> states_;
};



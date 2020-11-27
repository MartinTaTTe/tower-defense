#pragma once

class State {
public:
    State();
    ~State();
    virtual void EventHandler() = 0;
    virtual void Draw() = 0;
};


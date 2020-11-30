#include "state.hpp"

State::State(const std::string& state_name)
    : state_name_(state_name) { }

State::~State() { }

const std::string& State::GetName() const {
    return state_name_;
}

//
// Created by R1perXNX on 7/1/2024.
//

#ifndef PACMANV2_STATEMANAGER_H
#define PACMANV2_STATEMANAGER_H

#include <stack>
#include <memory>

template <typename T>
class StateManager {
protected:
    std::stack<std::unique_ptr<T>> states;

public:
    StateManager() = default;

    void PushState(std::unique_ptr<T> state);
    void PopState();
    void ClearStates();
    void Update();
    virtual ~StateManager();
};

template <typename T>
StateManager<T>::~StateManager() {
    while (!states.empty()) {
        states.top()->Exit();
        states.pop();
    }
}

template <typename T>
void StateManager<T>::PushState(std::unique_ptr<T> state) {
    if (!states.empty()) {
        states.top()->Exit();
    }
    states.push(std::move(state));
    states.top()->Enter();
}

template <typename T>
void StateManager<T>::PopState() {
    if (!states.empty()) {
        states.top()->Exit();
        states.pop();
    }
}

template <typename T>
void StateManager<T>::ClearStates() {
    while (!states.empty()) {
        states.top()->Exit();
        states.pop();
    }
}

template <typename T>
void StateManager<T>::Update() {
    if (!states.empty()) {
        states.top()->Update();
    }
}

#endif //PACMANV2_STATEMANAGER_H

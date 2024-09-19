//
// Created by R1perXNX on 7/13/2024.
//

#ifndef PACMANV2_IGAMESTATE_H
#define PACMANV2_IGAMESTATE_H

#include "SFML/Graphics.hpp"

namespace Game {
enum class GameStateType {
    NoState,
    MainMenu,
    Level,
    Pause,
    Victory,
    GameOver
};

class IGameState {
public:
    virtual void HandleTransition(GameStateType to) =0;
    virtual void Enter() = 0;
    virtual void Update() = 0;
    virtual void HandleMouseClick() = 0;
    virtual void HandleInput(sf::Event& event) = 0;
    virtual void Draw() = 0;
    virtual GameStateType GetType() = 0;
    virtual void Exit() = 0;
    virtual ~IGameState() = default;
};
}

#endif //PACMANV2_IGAMESTATE_H
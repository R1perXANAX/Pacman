//
// Created by R1perXNX on 7/13/2024.
//

#ifndef PACMANV2_GAMESTATEMANAGER_H
#define PACMANV2_GAMESTATEMANAGER_H
#include "../Logic/StatePattern/StateManager.h"
#include "GameStates/IGameState.h"

namespace Game {
class GameStateManager final : public StateManager<IGameState> {
public:
    GameStateManager() = default;
    ~GameStateManager() override = default;
    GameStateType GetCurrentState();
    void HandleInput();
    void Draw();
};
}

extern std::unique_ptr<Game::GameStateManager> GGameStateManager;

#endif //PACMANV2_GAMESTATEMANAGER_H

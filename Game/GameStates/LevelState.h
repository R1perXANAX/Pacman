//
// Created by R1perXNX on 7/1/2024.
//

#ifndef PACMANV2_LEVELSTATE_H
#define PACMANV2_LEVELSTATE_H

#include "IGameState.h"
#include "../../Logic/Entities/IAbstractFactory.h"
#include "../../Logic/World.h"

namespace Game {
class LevelState final : public IGameState {
    std::unique_ptr<Logic::World> world;
    sf::Text scoreLabel;
    sf::Text lifeLabel;
    sf::Text levelLabel;

public:
    LevelState() = default;
    void HandleTransition(GameStateType to) override;
    void Enter() override;
    void Exit() override;
    void Update() override;

    void HandleMouseClick() override {
    };
    void HandleInput(sf::Event& event) override;
    void Draw() override;

    inline GameStateType GetType() override {
        return GameStateType::Level;
    }

    ~LevelState() override = default;
};
}

#endif //PACMANV2_LEVELSTATE_H
//
// Created by R1perXNX on 7/1/2024.
//

#ifndef PACMANV2_VICTORYSTATE_H
#define PACMANV2_VICTORYSTATE_H

#include "GameOverState.h"

namespace Game {
class VictoryState final : public GameOverState {
public:
    VictoryState() = default;
    void HandleTransition(GameStateType to) override;
    void Enter() override;
    void Exit() override;
    void Update() override;

    void HandleMouseClick() override {
    };
    void HandleInput(sf::Event& event) override;
    void Draw() override;

    inline GameStateType GetType() override {
        return GameStateType::Victory;
    }

    ~VictoryState() override = default;
};
}

#endif //PACMANV2_VICTORYSTATE_H

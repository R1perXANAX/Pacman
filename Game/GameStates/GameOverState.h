//
// Created by R1perXNX on 7/1/2024.
//

#ifndef PACMANV2_GAMEOVERSTATE_H
#define PACMANV2_GAMEOVERSTATE_H
#include "IGameState.h"

namespace Game {
class GameOverState : public IGameState {
protected:
    sf::Font font;
    sf::Text text;
    sf::Text shadow;

public:
    GameOverState() = default;
    void HandleTransition(GameStateType to) override;
    void Enter() override;
    void Exit() override;
    void Update() override;

    void HandleMouseClick() override {
    };
    void HandleInput(sf::Event& event) override;
    void Draw() override;

    inline GameStateType GetType() override {
        return GameStateType::GameOver;
    }

    ~GameOverState() override = default;
};
}

#endif //PACMANV2_GAMEOVERSTATE_H
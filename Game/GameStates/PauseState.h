//
// Created by R1perXNX on 7/1/2024.
//

#ifndef PACMANV2_PAUSESTATE_H
#define PACMANV2_PAUSESTATE_H

#include "IGameState.h"
#include <array>

namespace Game {
class PauseState final : public IGameState {
private:
    sf::Font font;
    sf::Text text;
    sf::Vector2f buttonSize;
    sf::Vector2f buttonPos;
    unsigned int buttonPad{};
    std::array<sf::RectangleShape, 2> rects;
    std::array<sf::Text, 2> labels;

public:
    PauseState() = default;
    void HandleTransition(GameStateType to) override;
    void Enter() override;
    void Exit() override;
    void Update() override;
    void HandleMouseClick() override;
    void HandleInput(sf::Event& event) override;
    void Draw() override;

    inline GameStateType GetType() override {
        return GameStateType::Pause;
    }

    ~PauseState() override = default;
};
}

#endif //PACMANV2_PAUSESTATE_H
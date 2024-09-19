//
// Created by R1perXNX on 7/13/2024.
//

#include "GameStateManager.h"
#include "../View/GameWindow.h"
#include "../Game/Game.h"

using namespace View;
using namespace Game;

GameStateType GameStateManager::GetCurrentState() {
    if (!states.empty()) {
        return states.top()->GetType();
    } else {
        return GameStateType::NoState;
    }
}

void GameStateManager::HandleInput() {
    sf::Event event{};
    while (GameWindow::GetInstance().GetWindow().pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            game.Stop();
            return;
        }
        if (!states.empty()) {
            states.top()->HandleInput(event);
        }

    }

}

void GameStateManager::Draw() {
    if (!states.empty()) {
        states.top()->Draw();
    }
}

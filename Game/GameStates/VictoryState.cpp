//
// Created by R1perXNX on 7/1/2024.
//

#include "VictoryState.h"
#include "../GameStateManager.h"
#include "LevelState.h"

using namespace Game;

void VictoryState::HandleTransition(const GameStateType to) {
    switch (to) {
    case GameStateType::Level:
        GGameStateManager->ClearStates();
        GGameStateManager->PushState(std::make_unique<LevelState>());
        break;
    case GameStateType::MainMenu:
    case GameStateType::NoState:
    case GameStateType::Pause:
    case GameStateType::Victory:
    case GameStateType::GameOver:
        break;
    }
}

void VictoryState::Enter() {

    font.loadFromFile("../Resources/RetroGraphics.ttf");
    shadow.setString("VICTORY, press enter");
    text.setString("VICTORY, press enter");
    shadow.setFont(font);
    shadow.setCharacterSize(50);                // Large character size for emphasis
    shadow.setFillColor(sf::Color(50, 50, 50)); // Dark color for the shadow
    shadow.setPosition(42, 302);
    text.setFont(font);
    text.setCharacterSize(50);           // Same size as the shadow
    text.setFillColor(sf::Color::Green); // Choose a color that stands out
    text.setPosition(40, 300);
}

void VictoryState::Exit() {

}

void VictoryState::Update() {

}

void VictoryState::HandleInput(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Enter:
            HandleTransition(GameStateType::Level);
        default:
            break;
        }
    }
}

void VictoryState::Draw() {
    GameOverState::Draw();
}

//
// Created by R1perXNX on 7/1/2024.
//

#include "GameOverState.h"
#include "MenuState.h"
#include "../../View/GameWindow.h"
#include "../Game.h"
#include "../GameStateManager.h"
#include "../ScoreManager.h"

using namespace Game;
using namespace View;

void GameOverState::HandleTransition(GameStateType to) {
    switch (to) {
    case GameStateType::MainMenu:
        GGameStateManager->ClearStates();
        gScoreManager->SaveTopScores();
        gScoreManager->Reset();
        gScoreManager->ResetLevels();
        GGameStateManager->PushState(std::make_unique<MenuState>());
        break;
    case GameStateType::Level:
    case GameStateType::NoState:
    case GameStateType::Pause:
    case GameStateType::Victory:
    case GameStateType::GameOver:
    default:
        break;
    }
}

void GameOverState::Enter() {
    font.loadFromFile("../Resources/RetroGraphics.ttf");
    shadow.setString("GAME OVER, press enter");
    text.setString("GAME OVER, press enter");
    shadow.setFont(font);
    shadow.setCharacterSize(50);                // Large character size for emphasis
    shadow.setFillColor(sf::Color(50, 50, 50)); // Dark color for the shadow
    shadow.setPosition(42, 302);
    text.setFont(font);
    text.setCharacterSize(50);         // Same size as the shadow
    text.setFillColor(sf::Color::Red); // Choose a color that stands out
    text.setPosition(40, 300);
}

void GameOverState::Exit() {

}

void GameOverState::Update() {

}

void GameOverState::HandleInput(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Enter: {
            HandleTransition(GameStateType::MainMenu);
        }
        default:
            break;
        }
    }
    if (event.type == sf::Event::Closed) {
        game.Stop();
    }
}

void GameOverState::Draw() {
    GameWindow::GetInstance().GetWindow().clear();
    GameWindow::GetInstance().GetWindow().draw(shadow); // Draw the shadow first
    GameWindow::GetInstance().GetWindow().draw(text);   // Then draw the text
    GameWindow::GetInstance().GetWindow().display();
}
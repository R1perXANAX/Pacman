//
// Created by R1perXNX on 7/1/2024.
//

#include "PauseState.h"
#include "MenuState.h"
#include "../Game.h"
#include "../../View/GameWindow.h"
#include "../GameStateManager.h"
#include "../ScoreManager.h"

using namespace Game;
using namespace View;

void PauseState::HandleTransition(const GameStateType to) {
    switch (to) {
    case GameStateType::Level:
        GGameStateManager->PopState();
        break;
    case GameStateType::MainMenu:
        GGameStateManager->ClearStates();
        gScoreManager->Reset();
        gScoreManager->ResetLevels();
        GGameStateManager->PushState(std::make_unique<MenuState>());
        break;
    case GameStateType::NoState:
    case GameStateType::Pause:
    case GameStateType::Victory:
    case GameStateType::GameOver:
        break;
    }

}

void PauseState::Enter() {

    font.loadFromFile("../Resources/RetroGraphics.ttf");

    text.setFont(font);
    text.setString(sf::String("PAUSE:"));
    text.setCharacterSize(36);
    sf::FloatRect text_rect = text.getLocalBounds();
    text.setOrigin(text_rect.left + text_rect.width / 2.0f,
                   text_rect.top + text_rect.height / 2.0f);

    text.setPosition(SCREEN_WIDTH / 2, 100);
    buttonSize = sf::Vector2f(5.0f * SCREEN_MULT, .5f * SCREEN_MULT);
    buttonPos = sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - SCREEN_MULT);
    buttonPad = 4; // 4px.
    std::string str[2];
    str[0] = "CONTINUE";
    str[1] = "BACK TO MAIN MENU";

    for (int i = 0; i < 2; ++i) {
        sf::Vector2f buttonPosition(buttonPos.x, buttonPos.y +
                                                 (i * (buttonSize.y + buttonPad)));
        rects[i].setSize(buttonSize);
        rects[i].setFillColor(sf::Color::Blue);
        rects[i].setOrigin(buttonSize.x / 2.0f,
                           buttonSize.y / 2.0f);
        rects[i].setPosition(buttonPosition);
        labels[i].setFont(font);
        labels[i].setString(sf::String(str[i]));
        labels[i].setCharacterSize(20);
        const sf::FloatRect rect = labels[i].getLocalBounds();
        labels[i].setOrigin(rect.left + rect.width / 2.0f,
                            rect.top + rect.height / 2.0f);
        labels[i].setPosition(buttonPosition);
    }
}

void PauseState::Exit() {

}

void PauseState::Update() {

}

void PauseState::HandleInput(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            HandleMouseClick();
        }
    }
    if (event.type == sf::Event::Closed) {
        game.Stop();
    }
}

void PauseState::Draw() {

    GameWindow::GetInstance().GetWindow().clear(sf::Color::Black);

    GameWindow::GetInstance().GetWindow().draw(text);
    for (int i = 0; i < 2; ++i) {
        GameWindow::GetInstance().GetWindow().draw(rects[i]);
        GameWindow::GetInstance().GetWindow().draw(labels[i]);
    }

    GameWindow::GetInstance().GetWindow().display();
}

void PauseState::HandleMouseClick() {
    const sf::Vector2i mousePos = sf::Mouse::getPosition(GameWindow::GetInstance().GetWindow());
    const float halfX = buttonSize.x / 2.0f;
    const float halfY = buttonSize.y / 2.0f;

    for (int i = 0; i < 2; ++i) {
        if (mousePos.x >= rects[i].getPosition().x - halfX &&
            mousePos.x <= rects[i].getPosition().x + halfX &&
            mousePos.y >= rects[i].getPosition().y - halfY &&
            mousePos.y <= rects[i].getPosition().y + halfY) {
            if (i == 0) {
                HandleTransition(GameStateType::Level);
                return;
            } else if (i == 1) {
                HandleTransition(GameStateType::MainMenu);
                return;
            }
        }
    }
}
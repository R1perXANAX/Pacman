//
// Created by R1perXNX on 7/1/2024.
//

#include "LevelState.h"
#include "PauseState.h"
#include "VictoryState.h"
#include "GameOverState.h"
#include "../GameStateManager.h"
#include "../ScoreManager.h"
#include "../SoundManager.h"
#include "../ConcreteFactory.h"
#include "../Game.h"

using namespace Logic;
using namespace View;
using namespace Game;

void LevelState::Enter() {
    if (!world)
        world = std::make_unique<World>(std::make_unique<ConcreteFactory>());

    if (!world) {
        //Exit if world failed
        game.Stop();
        return;
    }

    world->SetMap(MapManager::GetInstance().GetCurrentMap());
    MapManager::GetInstance().NextMap();

    if (gScoreManager) //Increment the current level when we enter a game
        gScoreManager->IncrementLevel();

    if (gSoundManager)
        gSoundManager->LoadBackgroundSound("../Resources/level.wav");

    if (world->GetLocalPlayer())
        world->GetLocalPlayer()->Attach(gScoreManager);

    if (world->GetLocalPlayer() && gSoundManager)
        world->GetLocalPlayer()->Attach(gSoundManager);

    lifeLabel.setFont(GameWindow::GetInstance().GetFont());
    lifeLabel.setString("Lifes Left: ");
    lifeLabel.setCharacterSize(24);
    lifeLabel.setFillColor(sf::Color::Yellow);
    lifeLabel.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 25);

    scoreLabel.setFont(GameWindow::GetInstance().GetFont());
    scoreLabel.setString("Score:");
    scoreLabel.setCharacterSize(24);
    scoreLabel.setFillColor(sf::Color::Yellow);
    scoreLabel.setPosition(5, SCREEN_HEIGHT - 25);

    levelLabel.setFont(GameWindow::GetInstance().GetFont());
    levelLabel.setString("Current Level:");
    levelLabel.setCharacterSize(24);
    levelLabel.setFillColor(sf::Color::Yellow);
    levelLabel.setPosition(SCREEN_WIDTH - 200, SCREEN_HEIGHT - 25);
}

void LevelState::HandleTransition(const GameStateType to) {

    if (to == GameStateType::Pause) {
        GGameStateManager->PushState(std::make_unique<PauseState>());
        return;
    } else if (to == GameStateType::Victory) {
        GGameStateManager->PushState(std::make_unique<VictoryState>());
    } else if (to == GameStateType::GameOver) {
        GGameStateManager->PushState(std::make_unique<GameOverState>());
    }
}

void LevelState::Exit() {
    if (world->GetLocalPlayer()) {
        world->GetLocalPlayer()->Detach(gScoreManager);
        world->GetLocalPlayer()->Detach(gSoundManager);
    }
    if (gSoundManager)
        gSoundManager->StopBackground();
}

void LevelState::Update() {

    if (!world)
        return;

    if (gScoreManager) {
        if (gScoreManager->IsVictory())
            this->HandleTransition(GameStateType::Victory);
        else if (gScoreManager->IsGameOver())
            this->HandleTransition(GameStateType::GameOver);
    }

    world->Update();

    if (gSoundManager)
        gSoundManager->PlayBackground();
}

void LevelState::HandleInput(sf::Event& event) {
    if (!world)
        return;

    const auto localplayer = world->GetLocalPlayer();

    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Up:
            localplayer->SetNextDirection(Up);
            break;
        case sf::Keyboard::Down:
            localplayer->SetNextDirection(Down);
            break;
        case sf::Keyboard::Left:
            localplayer->SetNextDirection(Left);
            break;
        case sf::Keyboard::Right:
            localplayer->SetNextDirection(Right);
            break;
        case sf::Keyboard::Escape:
            HandleTransition(GameStateType::Pause);
            break;
        default:
            break;
        }
    }
}

void LevelState::Draw() {

    if (!world)
        return;

    auto localplayer = world->GetLocalPlayer();
    auto staticEntities = world->GetStaticEntities();
    auto ghosts = world->GetGhosts();

    GameWindow::GetInstance().GetWindow().clear();

    for (auto& row : staticEntities) {
        for (auto& entity : row) {
            if (entity)
                entity->Notify(SubjectEvent::Draw);
        }
    }

    if (localplayer)
        localplayer->Notify(SubjectEvent::Draw);

    for (auto& ghost : ghosts)
        if (ghost)
            ghost->Notify(SubjectEvent::Draw);

    if (gScoreManager) {
        auto score = gScoreManager->GetCurrentScore();
        sf::Text scoreValue;
        scoreValue.setString(std::to_string(score));
        scoreValue.setFont(GameWindow::GetInstance().GetFont());
        scoreValue.setCharacterSize(24);
        scoreValue.setFillColor(sf::Color::Yellow);
        scoreValue.setPosition(75, SCREEN_HEIGHT - 25);
        GameWindow::GetInstance().GetWindow().draw(scoreLabel);
        GameWindow::GetInstance().GetWindow().draw(scoreValue);

        auto lifeLeft = gScoreManager->GetLifeLeft();
        sf::Text lifeValue;
        lifeValue.setString(std::to_string(lifeLeft));
        lifeValue.setFont(GameWindow::GetInstance().GetFont());
        lifeValue.setCharacterSize(24);
        lifeValue.setFillColor(sf::Color::Yellow);
        lifeValue.setPosition(SCREEN_WIDTH / 2.f + 110, SCREEN_HEIGHT - 25);
        GameWindow::GetInstance().GetWindow().draw(lifeLabel);
        GameWindow::GetInstance().GetWindow().draw(lifeValue);

        auto currentLevel = gScoreManager->GetCurrentLevel();
        sf::Text levelValue;
        levelValue.setString(std::to_string(currentLevel));
        levelValue.setFont(GameWindow::GetInstance().GetFont());
        levelValue.setCharacterSize(24);
        levelValue.setFillColor(sf::Color::Yellow);
        levelValue.setPosition(SCREEN_WIDTH - 50, SCREEN_HEIGHT - 25);
        GameWindow::GetInstance().GetWindow().draw(levelLabel);
        GameWindow::GetInstance().GetWindow().draw(levelValue);

    }

    GameWindow::GetInstance().GetWindow().display();
}
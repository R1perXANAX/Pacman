//
// Created by R1perXNX on 7/3/2024.
//

#include "Game.h"
#include "../Logic/Camera.h"
#include "GameStateManager.h"
#include "../Game/GameStates/MenuState.h"
#include "MapManager.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "../Logic/StopWatch.h"

using namespace Logic;
using namespace Game;

void PacmanGame::Cleanup() {
    GGameStateManager->ClearStates();

}

PacmanGame::PacmanGame() {
    Camera::SetScreenSize({SCREEN_WIDTH, SCREEN_HEIGHT});
    Camera::SetWorldSize({MAP_COLUM_SIZE, MAP_ROW_SIZE});
    gScoreManager = std::make_shared<ScoreManager>();
    gSoundManager = std::make_shared<SoundManager>();
    GGameStateManager = std::make_unique<GameStateManager>();
    MapManager::GetInstance().LoadMaps("../Resources/Maps.json");
    if (gSoundManager && gScoreManager)
        running = true;
    else
        running = false;

    if (running) {
        GGameStateManager->PushState(std::make_unique<MenuState>());
    }
}

void PacmanGame::Run() const {
    Stopwatch::GetInstance().Start();
    while (running) {
        Stopwatch::GetInstance().UpdateDeltaTime();
        GGameStateManager->HandleInput();
        GGameStateManager->Update();
        GGameStateManager->Draw();
    }

    Stopwatch::GetInstance().Stop();
    Cleanup();
}

//
// Created by R1perXNX on 7/21/2024.
//

#include "SleepingState.h"
#include "RunningState.h"
#include "../PacmanEntity.h"

Logic::SleepingState::SleepingState(const std::shared_ptr<struct PacmanEntity>& pacmanEntity)
    : pacman(pacmanEntity) {

}

void Logic::SleepingState::Enter() {
    sleepingTime = std::chrono::steady_clock::now();
}

void Logic::SleepingState::Update() {
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - sleepingTime);
    if (elapsedTime.count() > SLEEP_COOLDOWN_SECONDS) {
        HandleTransition(PlayerStateType::PacmanRunning);
        return;
    }
}

void Logic::SleepingState::HandleTransition(const PlayerStateType to) {
    switch (to) {
    case PlayerStateType::PacmanRunning:
        if (auto pacmanEntity = pacman.lock()) {
            pacmanEntity->PopState();
        }
        break;
    default:
        break;
    }
}

void Logic::SleepingState::Exit() {
    if (auto pacmanEntity = pacman.lock()) {
        pacmanEntity->WakeUp(); //reset sleeping flag
    }
}

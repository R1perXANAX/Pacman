//
// Created by R1perXNX on 7/21/2024.
//

#ifndef PACMANV2_SLEEPINGSTATE_H
#define PACMANV2_SLEEPINGSTATE_H
#include "IPlayerState.h"
#include <chrono>
#include <memory>

namespace Logic {
class SleepingState final : public IPlayerState {
    std::weak_ptr<class PacmanEntity> pacman;
    std::chrono::steady_clock::time_point sleepingTime;
    static constexpr short SLEEP_COOLDOWN_SECONDS = 1;

public:
    SleepingState(const std::shared_ptr<class PacmanEntity>& pacmanEntity);
    ~SleepingState() override = default;
    void Enter() override;
    void Update() override;
    void HandleTransition(PlayerStateType to) override;
    PlayerStateType GetType() override { return PlayerStateType::PacmanSleeping; }
    void Exit() override;
};
}

#endif //PACMANV2_SLEEPINGSTATE_H

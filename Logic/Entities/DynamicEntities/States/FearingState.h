//
// Created by R1perXNX on 7/17/2024.
//

#ifndef PACMANV2_FEARINGSTATE_H
#define PACMANV2_FEARINGSTATE_H
#include "IPlayerState.h"
#include <chrono>
#include <memory>

namespace Logic {
class FearingState final : public IPlayerState {
protected:
    std::weak_ptr<class GhostEntity> ghost;
    std::chrono::steady_clock::time_point fearingTime;
    int FEAR_COOLDOWN_SECONDS;

public:
    FearingState(const std::shared_ptr<class GhostEntity>& currentGhost);
    ~FearingState() override = default;
    void Enter() override;
    void Update() override;
    void HandleTransition(PlayerStateType to) override;
    PlayerStateType GetType() override { return PlayerStateType::GhostFearing; }
    void Exit() override;
};
}

#endif //PACMANV2_FEARINGSTATE_H

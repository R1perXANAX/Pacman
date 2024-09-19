//
// Created by R1perXNX on 7/21/2024.
//

#ifndef PACMANV2_RUNNINGSTATE_H
#define PACMANV2_RUNNINGSTATE_H
#include <memory>
#include "../PacmanEntity.h"

namespace Logic {
class RunningState final : public IPlayerState {
    std::weak_ptr<class PacmanEntity> pacman;

private:
    //Helpers to pacman physics
    void Cornering() const;
    Direction CorrectDirection(Direction direction);
    void Collide() const;

public:
    RunningState(const std::shared_ptr<class PacmanEntity>& pacmanController);
    ~RunningState() override = default;
    void Enter() override;
    void Update() override;
    void HandleTransition(PlayerStateType to) override;
    PlayerStateType GetType() override { return PlayerStateType::PacmanSleeping; }
    void Exit() override;
};
}

#endif //PACMANV2_RUNNINGSTATE_H

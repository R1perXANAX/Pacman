//
// Created by R1perXNX on 7/17/2024.
//

#ifndef PACMANV2_CHASINGSTATE_H
#define PACMANV2_CHASINGSTATE_H
#include "IPlayerState.h"
#include <memory>

namespace Logic {
class ChasingState final : public IPlayerState {
protected:
    std::weak_ptr<class GhostEntity> ghost;

public:
    ChasingState(const std::shared_ptr<class GhostEntity>& currentGhost);
    ~ChasingState() override = default;
    void Enter() override;
    void Update() override;
    void HandleTransition(PlayerStateType to) override;
    PlayerStateType GetType() override { return PlayerStateType::GhostChasing; }
    void Exit() override;
};
}

#endif //PACMANV2_CHASINGSTATE_H

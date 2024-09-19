//
// Created by R1perXNX on 7/18/2024.
//

#ifndef PACMANV2_SETUPSTATE_H
#define PACMANV2_SETUPSTATE_H
#include <memory>
#include "IPlayerState.h"

namespace Logic {
class SetupState final : public IPlayerState {
protected:
    std::weak_ptr<class GhostEntity> ghost;

public:
    SetupState(const std::shared_ptr<class GhostEntity>& currentGhost);
    ~SetupState() override = default;
    void Enter() override;
    void Update() override;
    void HandleTransition(PlayerStateType to) override;
    PlayerStateType GetType() override { return PlayerStateType::GhostSetup; }
    void Exit() override;
};
}
#endif //PACMANV2_SETUPSTATE_H

//
// Created by R1perXNX on 7/17/2024.
//

#ifndef PACMANV2_IPLAYERSTATE_H
#define PACMANV2_IPLAYERSTATE_H

namespace Logic {
enum class PlayerStateType {
    GhostSetup,
    GhostFearing,
    GhostChasing,
    PacmanRunning,
    PacmanSleeping
};

class IPlayerState {
public:
    virtual void HandleTransition(PlayerStateType to) =0;
    virtual void Enter() = 0;
    virtual void Update() = 0;
    virtual PlayerStateType GetType() = 0;
    virtual void Exit() = 0;
    virtual ~IPlayerState() = default;
};
}

#endif //PACMANV2_IPLAYERSTATE_H

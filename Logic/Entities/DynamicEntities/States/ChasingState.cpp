//
// Created by R1perXNX on 7/17/2024.
//

#include "ChasingState.h"
#include "../../../World.h"
#include "FearingState.h"
#include "../GhostAI.h"
#include "SetupState.h"
#include "../../../StopWatch.h"

Logic::ChasingState::ChasingState(const std::shared_ptr<struct GhostEntity>& currentGhost)
    : ghost(currentGhost) {

}

void Logic::ChasingState::Enter() {
    if (const auto ghostEntity = ghost.lock()) {
        ghostEntity->AttachTarget(World::GetLocalPlayer());
    }
}

void Logic::ChasingState::Update() {

    if (const auto ghostEntity = ghost.lock()) {
        const auto target = ghostEntity->GetTarget();
        if (const auto targetEntity = target.lock())
            GhostAI::MoveGhost(targetEntity, ghostEntity, Stopwatch::GetDeltaTime());

        if (!ghostEntity->IsAlive()) {
            //Handle forced respawn from world
            HandleTransition(PlayerStateType::GhostSetup);
            return;
        }
        if (ghostEntity->IsFearing()) {
            HandleTransition(PlayerStateType::GhostFearing);
            return;
        }
    }
}

void Logic::ChasingState::HandleTransition(const PlayerStateType to) {
    switch (to) {
    case PlayerStateType::GhostFearing:
        if (auto ghostEntity = ghost.lock()) {
            ghostEntity->PushState(std::make_unique<FearingState>(ghostEntity));
        }
        break;
    case PlayerStateType::GhostSetup:
        if (auto ghostEntity = ghost.lock()) {
            ghostEntity->ClearStates();
            static short spawnCooldown = 1;
            ghostEntity->SetSpawnCooldown(spawnCooldown);
            spawnCooldown++;
            if (spawnCooldown == 5)
                spawnCooldown = 1;

            ghostEntity->PushState(std::make_unique<SetupState>(ghostEntity));
        }
        break;
    default:
        break;
    }
}

void Logic::ChasingState::Exit() {
}

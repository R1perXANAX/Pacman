//
// Created by R1perXNX on 7/18/2024.
//

#include "SetupState.h"
#include "FearingState.h"
#include "ChasingState.h"
#include "../GhostAI.h"
#include "../../../World.h"
#include "../../../StopWatch.h"

void Logic::SetupState::Enter() {
    if (const auto ghostEntity = ghost.lock()) {
        if (!ghostEntity->IsAlive()) {
            // Check if the ghost is alive
            ghostEntity->Spawn(); // If not, spawn the ghost
        }
        if (const auto checkPoint = World::GetGhostEscapePoint().lock()) {
            ghostEntity->AttachTarget(checkPoint); // Attach the escape point as the ghost's target
        }
    }
}

Logic::SetupState::SetupState(const std::shared_ptr<struct GhostEntity>& currentGhost)
    : ghost(currentGhost) {

}

void Logic::SetupState::Update() {

    if (const auto ghostEntity = ghost.lock()) {

        if (const auto checkPoint = World::GetGhostEscapePoint().lock()) {
            // Check if the ghost has reached the escape point
            if (ghostEntity->GetPosition().DistanceTo(checkPoint->GetPosition()) < 0.2) {
                HandleTransition(PlayerStateType::GhostChasing); // Transition to the chasing state
                return;
            }
        }

        const auto target = ghostEntity->GetTarget();
        if (const auto targetEntity = target.lock())
            GhostAI::MoveGhost(targetEntity, ghostEntity, Stopwatch::GetDeltaTime(), true);
        // Move the ghost towards the target

        // Check if the ghost is in a fearing state
        if (ghostEntity->IsFearing()) {
            HandleTransition(PlayerStateType::GhostFearing);
        }
    }
}

void Logic::SetupState::HandleTransition(const PlayerStateType to) {
    if (auto ghostEntity = ghost.lock()) {
        switch (to) {
        case PlayerStateType::GhostFearing:
            ghostEntity->PushState(std::make_unique<FearingState>(ghostEntity));
            break;
        case PlayerStateType::GhostChasing:
            ghostEntity->ClearStates();
            ghostEntity->PushState(std::make_unique<ChasingState>(ghostEntity));
            break;
        default:
            break;
        }
    }
}

void Logic::SetupState::Exit() {

}

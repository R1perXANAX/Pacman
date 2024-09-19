//
// Created by R1perXNX on 7/17/2024.
//

#include "FearingState.h"
#include "../GhostEntity.h"
#include "../GhostAI.h"
#include "../../../StopWatch.h"
#include "../../../../Game/ScoreManager.h"
#include "SetupState.h"

Logic::FearingState::FearingState(const std::shared_ptr<GhostEntity>& currentGhost)
    : ghost(currentGhost) {
    FEAR_COOLDOWN_SECONDS = static_cast<int>(5 / gScoreManager->GetCurrentLevel()) + 1;
}


void Logic::FearingState::Enter() {
    if (const auto ghostEntity = ghost.lock()) {
        // Set the ghost's direction to the opposite of its current direction
        ghostEntity->SetDirection(ghostEntity->GetOppositeDirection(ghostEntity->GetDirection()));
        fearingTime = std::chrono::steady_clock::now();

        // Reduce the ghost's speed for the duration of the fearing state
        ghostEntity->SetSpeed(ghostEntity->GetOriginalSpeed() / 1.5f);
        ghostEntity->ToggleFearing();
    }
}

void Logic::FearingState::Exit() {
    if (const auto ghostEntity = ghost.lock()) {
        // Restore the ghost's speed to its original value
        ghostEntity->SetSpeed(ghostEntity->GetOriginalSpeed());
    }
}

void Logic::FearingState::Update() {
    if (const auto ghostEntity = ghost.lock()) {
        if (!ghostEntity->IsAlive()) {
            HandleTransition(PlayerStateType::GhostSetup);
            return;
        }

        if (const auto targetEntity = ghostEntity->GetTarget().lock()) {
            // Move the ghost towards its target
            GhostAI::MoveGhost(targetEntity, ghostEntity, Stopwatch::GetDeltaTime());
        }
    }
    const auto currentTime = std::chrono::steady_clock::now();
    const auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - fearingTime);
    if (elapsedTime.count() > FEAR_COOLDOWN_SECONDS) {
        HandleTransition(PlayerStateType::GhostChasing);
        return;
    }

}

void Logic::FearingState::HandleTransition(const PlayerStateType to) {

    switch (to) {
    case PlayerStateType::GhostChasing:
        if (const auto ghostEntity = ghost.lock()) {
            ghostEntity->PopState();
        }
        break;
    case PlayerStateType::GhostSetup:
        if (auto ghostEntity = ghost.lock()) {
            ghostEntity->ClearStates();
            ghostEntity->SetSpawnCooldown(1);
            ghostEntity->PushState(std::make_unique<SetupState>(ghostEntity));
        }
        break;
    default:
        break;
    }
}

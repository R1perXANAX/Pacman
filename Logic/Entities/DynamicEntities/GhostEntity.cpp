//
// Created by R1perXNX on 7/3/2024.
//

#include "GhostEntity.h"
#include "States/FearingState.h"

using namespace Logic;

void GhostEntity::AttachTarget(const std::shared_ptr<EntityModel>& newTarget) {
    target = newTarget;
}

GhostEntity::GhostEntity(EntityType type, const Vector2f& position, float speed, Direction direction)
    : DynamicEntityModel(type, position, speed, direction) {
    originalSpeed = speed;
    spawnTime = std::chrono::steady_clock::now();

}

void GhostEntity::Move(const float deltatime) {
    if (!CanMove()) // Check if the ghost is allowed to move (based on spawn cooldown)
        return;

    // Calculate the new position based on the direction, speed, and elapsed time
    const Vector2f newPosition = position + (directionVectors[direction] * speed * deltatime);
    SetPosition(newPosition);

}


void GhostEntity::Spawn() {
    this->SetPosition(spawnPos);
    alive = true;
}

// Kills the ghost, marking it as not alive and recording the death time.
void GhostEntity::Kill() {
    alive = false;
    deathTime = std::chrono::steady_clock::now();
    spawnTime = std::chrono::steady_clock::now();
}


bool GhostEntity::CanMove() const {
    const auto currentTime = std::chrono::steady_clock::now();
    const auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - spawnTime);
    return elapsedTime.count() >= SPAWN_COOLDOWN_SECONDS;
}

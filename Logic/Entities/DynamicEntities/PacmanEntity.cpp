//
// Created by R1perXNX on 7/3/2024.
//

#include "PacmanEntity.h"
#include "States/RunningState.h"

using namespace Logic;

void PacmanEntity::Take(const std::shared_ptr<EntityModel>& collectable) {
    if (!collectable)
        return;

    collectable->SetAvailable(false);
    EntityModel::Notify(SubjectEvent::CoinEaten);
}

void PacmanEntity::Eat(const std::shared_ptr<EntityModel>& collectable) {
    if (!collectable)
        return;

    collectable->SetAvailable(false);
    EntityModel::Notify(SubjectEvent::FruitEaten);
}

void PacmanEntity::Move(const float deltatime) {
    if (!CanMove())
        return;

    Vector2f newPosition = position + (directionVectors[direction] * speed * deltatime);
    SetPosition(newPosition);
}


void PacmanEntity::Kill() {
    isDead = true;
    isStopped = true;
    direction = Direction::None;
    nextDirection = Direction::None;
}

void PacmanEntity::Spawn() {
    isDead = false;
    isStopped = false;
    direction = Direction::Up;
    SetPosition(spawnPos);
    this->ClearStates();
    this->PushState(std::make_unique<RunningState>(shared_from_this()));
}

PacmanEntity::PacmanEntity(const EntityType type, const Vector2f& position, float speed, Direction direction)
    : DynamicEntityModel(type, position, speed, direction) {
    isDead = false;
    isStopped = false;
}

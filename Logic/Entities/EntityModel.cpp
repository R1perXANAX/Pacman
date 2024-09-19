//
// Created by R1perXNX on 7/3/2024.
//

#include "EntityModel.h"
#include <algorithm>
using namespace Logic;

EntityModel::EntityModel(EntityType type, const Vector2f& position)
    : type(type), position(position) {
    spawnPos = position;
    origin.x = position.x + size.x / 2;
    origin.y = position.y + size.y / 2;
}

EntityModel::~EntityModel() {
    observers.clear();
}

void EntityModel::Attach(std::shared_ptr<IObserver> observer) {
    observers.push_back(observer);
}

void EntityModel::Detach(std::shared_ptr<IObserver> observer) {
    const auto it = std::remove(observers.begin(), observers.end(), observer);
    observers.erase(it, observers.end());
}

void EntityModel::Notify(const SubjectEvent& event) {
    for (const auto& observer : observers) {
        observer->Update(event);
    }
}

Vector2f EntityModel::GetPosition() const {
    return position;
}

Vector2f EntityModel::GetOrigin() const {
    return origin;
}

void EntityModel::SetPosition(const Vector2f& newPosition) {
    position = newPosition;
    origin.x = position.x + size.x / 2;
    origin.y = position.y + size.y / 2;
}

void EntityModel::SetOrigin(const Vector2f& newOrigin) {
    origin = newOrigin;
    position.x = origin.x - size.x / 2;
    position.y = origin.y - size.y / 2;
}

void EntityModel::CenterObject(Direction direction) {
    Vector2f newOrigin = GetOrigin();

    switch (direction) {
    case Direction::Up:
    case Direction::Down:
        newOrigin.x = static_cast<int>(newOrigin.x) + 0.5;
        break;
    case Direction::Left:
    case Direction::Right:
        newOrigin.y = static_cast<int>(newOrigin.y) + 0.5;
    default:
        break;
    }

    SetOrigin(newOrigin);
}

void EntityModel::Spawn() {
    SetPosition(spawnPos);
}
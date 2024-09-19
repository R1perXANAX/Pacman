//
// Created by R1perXNX on 7/3/2024.
//

#include "CollectableEntity.h"

using namespace Logic;

void WallEntity::Spawn() {
    SetPosition(spawnPos);
}

void CollectableEntity::Spawn() {
    SetPosition(spawnPos);
}
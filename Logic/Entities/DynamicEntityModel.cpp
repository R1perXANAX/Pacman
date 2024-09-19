//
// Created by R1perXNX on 7/3/2024.
//

#include "DynamicEntityModel.h"
using namespace Logic;
const std::array<Vector2f, 5> DynamicEntityModel::directionVectors = {{
    {0, 0},
    {0, -1},
    {0, 1},
    {-1, 0},
    {1, 0}
}};

const std::array<Direction, 5> DynamicEntityModel::oppositeDirections = {None, Down, Up, Right, Left};

DynamicEntityModel::DynamicEntityModel(const EntityType type, const Vector2f& position, float speed,
                                       Direction direction)
    : EntityModel(type, position) {
    this->speed = speed;
    this->direction = direction;
}

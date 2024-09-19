//
// Created by R1perXNX on 7/17/2024.
//

#ifndef PACMANV2_GHOSTAI_H
#define PACMANV2_GHOSTAI_H

#include "GhostEntity.h"

namespace Logic {
namespace GhostAI {
bool IsInTunnel(const std::shared_ptr<DynamicEntityModel>& entity);
bool IsInMiddleTile(const Vector2f& pos, const Vector2f& prev, Direction dir);
std::vector<Direction> GetAvailableDirections(const std::shared_ptr<DynamicEntityModel>& entity, Direction dir);
Direction ManhattanDistance(const std::shared_ptr<EntityModel>& target, const std::shared_ptr<GhostEntity>& ghost,
                            const std::vector<Direction>& availableDirections);
void MoveGhost(const std::shared_ptr<EntityModel>& target, const std::shared_ptr<GhostEntity>& ghost,
               float deltaTime, bool disableRandomness = false);
};
}
#endif //PACMANV2_GHOSTAI_H

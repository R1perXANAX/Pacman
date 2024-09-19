//
// Created by R1perXNX on 7/17/2024.
//

#include "GhostAI.h"
#include "../../World.h"
#include "PacmanEntity.h"
#include "../../Random.h"

#include <queue>
#include <limits>

using namespace Logic;

// Checks if the ghost is in a tunnel, defined by specific x-coordinate boundaries.
bool GhostAI::IsInTunnel(const std::shared_ptr<DynamicEntityModel>& entity) {
    const auto position = entity->GetPosition();
    return position.x < 0 || position.x > 20;
}

// Checks if the ghost is in the middle of a tile, used for determining when to change direction.
bool GhostAI::IsInMiddleTile(const Vector2f& pos, const Vector2f& prev, const Direction dir) {

    // Ensure the ghost is still within the same tile.
    if (static_cast<int>(pos.x) != static_cast<int>(prev.x) || static_cast<int>(pos.y) != static_cast<int>(prev.y))
        return false;
    const float x = pos.x - static_cast<int>(pos.x);
    const float y = pos.y - static_cast<int>(pos.y);

    const float px = prev.x - static_cast<int>(prev.x);
    const float py = prev.y - static_cast<int>(prev.y);

    // Check if the ghost has crossed the midpoint of the tile in its current direction.
    switch (dir) {
    case Up:
    case Down:
        return std::min(y, py) <= 0.5f && std::max(y, py) >= 0.5f;
        break;

    case Left:
    case Right:
        return std::min(x, px) <= 0.5f && std::max(x, px) >= 0.5f;
        break;
    case None:
        break;
    }
    return false;
}

// Returns a list of available directions the ghost can move, excluding the opposite direction.
std::vector<Direction> GhostAI::GetAvailableDirections(const std::shared_ptr<DynamicEntityModel>& entity,
                                                       const Direction dir) {
    std::vector<Direction> dirs;

    // Check each direction for wall collisions and add valid directions to the list.
    if (!World::CheckWallCollision(entity, Right, 0.9f))
        dirs.push_back(Right);
    if (!World::CheckWallCollision(entity, Down, 0.9f))
        dirs.push_back(Down);
    if (!World::CheckWallCollision(entity, Left, 0.9f))
        dirs.push_back(Left);
    if (!World::CheckWallCollision(entity, Up, 0.9f))
        dirs.push_back(Up);

    // If only two directions are available, remove the opposite direction from the list,  preventing the ghost from turning around and moving back in the direction it just came from.
    if (dirs.size() == 2) {
        for (int i = 0; i < dirs.size(); i++) {
            if (dirs[i] == entity->GetOppositeDirection(dir)) {
                dirs.erase(dirs.begin() + i);
                break; // Break after erasing to avoid skipping elements
            }
        }
    }
    return dirs;
}

Direction GhostAI::ManhattanDistance(const std::shared_ptr<EntityModel>& target,
                                     const std::shared_ptr<GhostEntity>& ghost,
                                     const std::vector<Direction>& availableDirections) {

    if (!target)
        return Direction::None;

    Direction best_dir = Direction::None;
    float min = std::numeric_limits<float>::max();
    float max = 0.f;
    if (availableDirections.size() == 1)
        return availableDirections.at(0);

    for (auto& direction : availableDirections) {

        auto calc_distance = [](const Vector2f& p1, const Vector2f& p2) {
            return (float)(std::abs(p1.x - p2.x) + std::abs(p1.y - p2.y));
        };

        auto prediction = ghost->GetOrigin() + ghost->GetDirectionVector(direction);
        const auto distance = calc_distance(target->GetOrigin(), prediction);
        if (distance < min) {
            best_dir = direction;
            min = distance;
        }

    }
    return best_dir;
}


// Moves the ghost towards the target, optionally disabling randomness for deterministic behavior.
void GhostAI::MoveGhost(const std::shared_ptr<EntityModel>& target, const std::shared_ptr<GhostEntity>& ghost,
                        const float deltaTime, const bool disableRandomness) {

    if (ghost && target) {

        const auto prev_pos = ghost->GetOrigin();
        ghost->Move(deltaTime); // Move the ghost based on its current direction and speed.

        // Check if the ghost should update its direction, considering if it's in a tunnel or middle of a tile.
        if (!ghost->updateDirection && !IsInTunnel(ghost) && IsInMiddleTile(
                ghost->GetOrigin(), prev_pos, ghost->GetDirection())) {
            const auto availableDirections = GetAvailableDirections(ghost, ghost->GetDirection());

            auto& random = Random::GetInstance();
            Direction newDirection = None;
            auto number = random.GetRandomInRange(0, 1);

            if (disableRandomness)
                number = 1;

            // Determine the new direction based on the ghost's state and whether randomness is allowed.
            if (ghost->GetStateType() == PlayerStateType::GhostFearing) {
                newDirection = availableDirections[random.GetRandomInRange(
                    0, static_cast<int>(availableDirections.size()) - 1)];
            } else {
                if (!number)
                    newDirection = availableDirections[random.GetRandomInRange(
                        0, static_cast<int>(availableDirections.size()) - 1)];
                else
                    newDirection = ManhattanDistance(target, ghost, availableDirections);
            }

            ghost->SetDirection(newDirection);          // Update the ghost's direction.
            ghost->CenterObject(ghost->GetDirection()); // Center the ghost on the grid.
            ghost->updateDirection = true;              // Mark that the direction has been updated.
        } else {
            ghost->updateDirection = false; // If not updating direction, mark accordingly.
        }

        // Handle tunnel wrapping (ghosts moving off one side of the screen and appearing on the other).
        auto position = ghost->GetPosition();

        if (position.x < -1) {
            position.x += 22; // Wrap around to the right side
            ghost->SetPosition(position);
        } else if (position.x >= 22) {
            position.x -= 22; // Wrap around to the left side
            ghost->SetPosition(position);
        }
    }
}

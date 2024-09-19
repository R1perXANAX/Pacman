//
// Created by R1perXNX on 7/3/2024.
//

#include "PacmanController.h"
#include "../../World.h"
#include "../../StopWatch.h"

using namespace Logic;

// Handles Pacman's cornering logic, adjusting its position as it turns
void PacmanController::Cornering() const {
    const auto newPosition = pacman->GetOrigin() + (
                                 pacman->GetDirectionVector(pacman->dirCorrection) * pacman->speed *
                                 Stopwatch::GetDeltaTime());

    pacman->SetOrigin(newPosition);

    bool done = false;

    // Determine if Pacman has completed the cornering based on the direction correction.
    switch (pacman->dirCorrection) {
    case Up:
        done = (pacman->origin.y - static_cast<int>(pacman->origin.y) <= 0.5f);
        break;
    case Down:
        done = (pacman->origin.y - static_cast<int>(pacman->origin.y) >= 0.5f);
        break;
    case Left:
        done = (pacman->origin.x - static_cast<int>(pacman->origin.x) <= 0.5f);
        break;
    case Right:
        done = (pacman->origin.x - static_cast<int>(pacman->origin.x) >= 0.5f);
        break;
    case None:
        break;
    }

    // If cornering is complete, center Pacman on the grid and stop cornering.
    if (done) {
        pacman->CenterObject(pacman->direction);
        pacman->isCornering = false;
    }
}

// Determines the corrected direction for Pacman when cornering.
Direction PacmanController::CorrectDirection(const Direction direction) const {
    const auto origin = pacman->GetOrigin();

    // Depending on the current direction, determine the appropriate correction.
    switch (direction) {
    case Up:
    case Down:
        if (origin.x - static_cast<int>(origin.x) >= 0.5f)
            return Left;
        return Right;
        break;
    case Left:
    case Right:
        if (origin.y - static_cast<int>(origin.y) >= 0.5f)
            return Up;
        return Down;
        break;
    case None:
    default:
        return None;
    }
}

// Handles the logic for Pacman colliding with walls.
void PacmanController::Collide() const {
    auto origin = pacman->GetOrigin();

    // Adjust Pacman's origin based on its current direction to align it with the grid.
    switch (pacman->GetDirection()) {
    case Up:
    case Down:
        origin.y = static_cast<int>(origin.y) + 0.5f;
        break;
    case Left:
    case Right:
        origin.x = static_cast<int>(origin.x) + 0.5f;
        break;
    case None:
        return;
    }

    pacman->SetOrigin(origin); // Update Pacman's origin to the corrected position
}

// Updates Pacman's movement and state based on input and game conditions.
void PacmanController::Update() const {
    if (pacman && pacman->IsAlive()) {

        Direction nextDir = None;
        if (pacman->IsNewDirection())
            nextDir = pacman->GetNextDirection();

        // If the new direction is valid and there is no wall collision, update Pacman's direction.
        if (nextDir != None && !World::CheckWallCollision(pacman, nextDir, 0.51)) {
            pacman->SetDirection(nextDir);

            // If the new direction is not the opposite of the current direction, start cornering.
            if (pacman->GetDirection() != pacman->GetOppositeDirection(pacman->GetDirection())) {
                pacman->isCornering = true;
                pacman->dirCorrection = CorrectDirection(nextDir);
            }
        }

        // Move Pacman if it is allowed to move.
        if (pacman->CanMove())
            pacman->Move(Stopwatch::GetDeltaTime());

        // Handle cornering if Pacman is currently cornering.
        if (pacman->isCornering)
            Cornering();

        // Check for wall collisions in the current direction.
        if (World::CheckWallCollision(pacman, pacman->GetDirection(), 0.51)) {
            Collide();
            pacman->Stop();
        } else {
            pacman->Start();
        }

        auto position = pacman->GetPosition();

        // Handle Pacman moving through tunnels (wrapping around the screen).
        if (position.x <= -1) {
            position.x = 22;
            pacman->SetPosition(position);
        } else if (position.x >= 22) {
            position.x -= 22;
            pacman->SetPosition(position);
        }
    }
}

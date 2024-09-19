//
// Created by R1perXNX on 7/21/2024.
//

#include "RunningState.h"
#include "../PacmanEntity.h"
#include "SleepingState.h"
#include "../../../World.h"
#include "../../../StopWatch.h"

Logic::RunningState::RunningState(const std::shared_ptr<PacmanEntity>& pacmanEntity)
    : pacman(pacmanEntity) {

}

void Logic::RunningState::Enter() {

}

void Logic::RunningState::Update() {
    if (const auto pacmanEntity = pacman.lock()) {

        if (pacmanEntity->IsSleeping())
            HandleTransition(PlayerStateType::PacmanSleeping);

        Direction nextDir = None;
        if (pacmanEntity->IsNewDirection())
            nextDir = pacmanEntity->GetNextDirection();

        if (nextDir != None && !World::CheckWallCollision(pacmanEntity, nextDir, 0.51)) {
            pacmanEntity->SetDirection(nextDir);

            if (pacmanEntity->GetDirection() != pacmanEntity->GetOppositeDirection(pacmanEntity->GetDirection())) {
                pacmanEntity->Corner(true);
                pacmanEntity->SetCorrectDirection(CorrectDirection(nextDir));
            }
        }

        if (pacmanEntity->CanMove())
            pacmanEntity->Move(Stopwatch::GetDeltaTime());

        if (pacmanEntity->IsCornering())
            Cornering();

        if (World::CheckWallCollision(pacmanEntity, pacmanEntity->GetDirection(), 0.51)) {
            Collide();
            pacmanEntity->Stop();
        } else {
            pacmanEntity->Start();
        }

        auto position = pacmanEntity->GetPosition();

        if (position.x < -1) {
            position.x += 22;
            pacmanEntity->SetPosition(position);
        } else if (position.x >= 22) {
            position.x -= 22;
            pacmanEntity->SetPosition(position);
        }
    }

}

void Logic::RunningState::HandleTransition(const PlayerStateType to) {

    switch (to) {
    case PlayerStateType::PacmanSleeping: {
        if (auto pacmanEntity = pacman.lock()) {
            pacmanEntity->PushState(std::make_unique<SleepingState>(pacmanEntity));
        }
    default:
        break;
    }
    }
}

void Logic::RunningState::Exit() {

}

void Logic::RunningState::Cornering() const {

    if (const auto pacmanEntity = pacman.lock()) {
        const auto newPosition = pacmanEntity->GetOrigin() + (
                                     pacmanEntity->GetDirectionVector(pacmanEntity->GetDirectionCorrection()) *
                                     pacmanEntity->GetSpeed() *
                                     Stopwatch::GetDeltaTime());

        pacmanEntity->SetOrigin(newPosition);

        bool done = false;

        switch (pacmanEntity->GetDirectionCorrection()) {
        case Up:
            done = (pacmanEntity->GetOrigin().y - static_cast<int>(pacmanEntity->GetOrigin().y) <= 0.5f);
            break;
        case Down:
            done = (pacmanEntity->GetOrigin().y - static_cast<int>(pacmanEntity->GetOrigin().y) >= 0.5f);
            break;
        case Left:
            done = (pacmanEntity->GetOrigin().x - static_cast<int>(pacmanEntity->GetOrigin().x) <= 0.5f);
            break;
        case Right:
            done = (pacmanEntity->GetOrigin().x - static_cast<int>(pacmanEntity->GetOrigin().x) >= 0.5f);
            break;
        case None:
            break;
        }

        if (done) {
            pacmanEntity->CenterObject(pacmanEntity->GetDirection());
            pacmanEntity->Corner(false);
        }
    }
}

Logic::Direction Logic::RunningState::CorrectDirection(const Direction direction) {
    if (const auto pacmanEntity = pacman.lock()) {
        const auto origin = pacmanEntity->GetOrigin();

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
        default:
            return None;
        }
    }
    return None;
}

void Logic::RunningState::Collide() const {
    if (const auto pacmanEntity = pacman.lock()) {
        auto origin = pacmanEntity->GetOrigin();

        switch (pacmanEntity->GetDirection()) {
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

        pacmanEntity->SetOrigin(origin);
    }
}

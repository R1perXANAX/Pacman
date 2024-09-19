//
// Created by R1perXNX on 7/3/2024.
//

#ifndef PACMANV2_GHOSTENTITY_H
#define PACMANV2_GHOSTENTITY_H
#include "../../StatePattern/StateManager.h"
#include "../DynamicEntityModel.h"
#include "States/IPlayerState.h"
#include <chrono>

namespace Logic {
class GhostEntity final
    : public DynamicEntityModel, public StateManager<IPlayerState>, public std::enable_shared_from_this<GhostEntity> {
protected:
    std::chrono::steady_clock::time_point spawnTime;
    std::chrono::steady_clock::time_point deathTime;
    short SPAWN_COOLDOWN_SECONDS = 1;


    float originalSpeed;
    bool alive{false};
    bool fearing{false};
    std::weak_ptr<EntityModel> target;

public:
    GhostEntity(EntityType type, const Vector2f& position, float speed = 0, Direction direction = Direction::Up);
    ~GhostEntity() override = default;

    bool updateDirection{false};
    float GetOriginalSpeed() const { return originalSpeed; }
    PlayerStateType GetStateType() { return states.top()->GetType(); }
    bool IsAlive() const { return alive; }
    bool IsFearing() const { return fearing; }
    bool CanMove() const;
    void SetSpawnCooldown(const short seconds) { SPAWN_COOLDOWN_SECONDS = seconds; }
    void ToggleFearing() { fearing = !fearing; }
    std::weak_ptr<EntityModel> GetTarget() { return target; }
    void AttachTarget(const std::shared_ptr<EntityModel>& newTarget);

    void Move(float deltatime) override;

    void Stop() override {
    };
    void Kill() override;
    void Spawn() override;

};
}

#endif //PACMANV2_GHOSTENTITY_H

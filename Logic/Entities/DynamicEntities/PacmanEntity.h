//
// Created by R1perXNX on 7/3/2024.
//

#ifndef PACMANV2_PACMANENTITY_H
#define PACMANV2_PACMANENTITY_H
#include "../DynamicEntityModel.h"
#include "States/IPlayerState.h"
#include "../../StatePattern/StateManager.h"

namespace Logic {
class PacmanEntity final : public DynamicEntityModel, public StateManager<IPlayerState>,
                           public std::enable_shared_from_this<PacmanEntity> {
private:
    bool isCornering{false};
    bool isDead{false};
    bool isStopped{true};
    bool isSleeping{false};
    Direction dirCorrection{None};

public:
    inline bool IsAlive() const { return !isDead; }
    inline bool CanMove() const { return !isStopped; }

    inline void Start() { isStopped = false; }

    void Take(const std::shared_ptr<EntityModel>& collectable);
    void Eat(const std::shared_ptr<EntityModel>& collectable);

    void Stop() override { isStopped = true; };
    void Sleep() { isSleeping = true; }
    void WakeUp() { isSleeping = false; }
    bool IsSleeping() const { return isSleeping; }
    float GetSpeed() const { return speed; }
    Direction GetDirectionCorrection() const { return dirCorrection; }
    void SetCorrectDirection(const Direction& correction) { dirCorrection = correction; }
    void Corner(const bool cornering) { isCornering = cornering; }
    bool IsCornering() const { return isCornering; }
    void Move(float deltatime) override;
    void Kill() override;
    void Spawn() override;

    PacmanEntity(EntityType type, const Vector2f& position, float speed = 0, Direction direction = Up);
    ~PacmanEntity() override = default;
    friend class PacmanController;
};
}
#endif //PACMANV2_PACMANENTITY_H

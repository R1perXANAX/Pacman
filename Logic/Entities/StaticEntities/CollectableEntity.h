//
// Created by R1perXNX on 7/3/2024.
//

#ifndef PACMANV2_COLLECTABLEENTITY_H
#define PACMANV2_COLLECTABLEENTITY_H
#include "../EntityModel.h"

namespace Logic {
class CollectableEntity : public EntityModel {
protected:
    bool bAvailable;

public:
    inline bool IsAvailable() override { return bAvailable; }
    inline void SetAvailable(const bool available) override { bAvailable = available; }
    void Spawn() override;

    CollectableEntity(const EntityType type, const Vector2f& position, const bool available)
        : EntityModel(type, position), bAvailable(available) {
    };
    ~CollectableEntity() override = default;
};

class WallEntity final : public EntityModel {
public:
    WallEntity(const EntityType type, const Vector2f& position)
        : EntityModel(type, position) {
    };
    ~WallEntity() override = default;
    void Spawn() override;
};

class FruitEntity : public CollectableEntity {
public:
    FruitEntity(const EntityType type, const Vector2f& position, const bool available)
        : CollectableEntity(type, position, available) {
    };
    ~FruitEntity() override = default;
};

class CoinEntity final : public CollectableEntity {

public:
    CoinEntity(const EntityType type, const Vector2f& position, const bool available)
        : CollectableEntity(type, position, available) {
    };
    ~CoinEntity() override = default;
};

class BananaEntity final : public FruitEntity {
    ;

public:
    BananaEntity(const EntityType type, const Vector2f& position, const bool available)
        : FruitEntity(type, position, available) {
    }

    ~BananaEntity() override = default;
};
}
#endif //PACMANV2_COLLECTABLEENTITY_H
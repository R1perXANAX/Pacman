//
// Created by R1perXNX on 7/3/2024.
//

#ifndef PACMANV2_IABSTRACTFACTORY_H
#define PACMANV2_IABSTRACTFACTORY_H

#include "EntityModel.h"
#include "DynamicEntities/PacmanEntity.h"
#include "DynamicEntities/GhostEntity.h"
#include "StaticEntities/CollectableEntity.h"

class IAbstractFactory {
public:
    virtual std::shared_ptr<Logic::PacmanEntity> CreatePacman(const Vector2f& position, float speed) const = 0;
    virtual std::shared_ptr<Logic::GhostEntity> CreateGhost(const Vector2f& position, float speed) const = 0;
    virtual std::shared_ptr<Logic::EntityModel> CreateWall(const Vector2f& position) const = 0;
    virtual std::shared_ptr<Logic::CollectableEntity> CreateCoin(const Vector2f& position) const = 0;
    virtual std::shared_ptr<Logic::CollectableEntity> CreateFruit(const Vector2f& position) const = 0;
    virtual std::shared_ptr<Logic::BananaEntity> CreateBanana(const Vector2f& position) const = 0;
    virtual ~IAbstractFactory() = default;
};


#endif //PACMANV2_IABSTRACTFACTORY_H
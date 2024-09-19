//
// Created by R1perXNX on 7/3/2024.
//

#ifndef PACMANV2_CONCRETEFACTORY_H
#define PACMANV2_CONCRETEFACTORY_H

#include "../Logic/Entities/IAbstractFactory.h"
#include "../Logic/Entities/DynamicEntities/PacmanEntity.h"
#include "../Logic/Entities/DynamicEntities/GhostEntity.h"
#include "../View/Entities/StaticEntities/CollectableView.h"


class ConcreteFactory final : public IAbstractFactory {
public:
    std::shared_ptr<Logic::PacmanEntity> CreatePacman(const Vector2f& position, float speed) const override;
    std::shared_ptr<Logic::GhostEntity> CreateGhost(const Vector2f& position, float speed) const override;
    std::shared_ptr<Logic::EntityModel> CreateWall(const Vector2f& position) const override;
    std::shared_ptr<Logic::CollectableEntity> CreateCoin(const Vector2f& position) const override;
    std::shared_ptr<Logic::CollectableEntity> CreateFruit(const Vector2f& position) const override;
    std::shared_ptr<Logic::BananaEntity> CreateBanana(const Vector2f& position) const override;
};


#endif //PACMANV2_CONCRETEFACTORY_H

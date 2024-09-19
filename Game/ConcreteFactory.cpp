//
// Created by R1perXNX on 7/3/2024.
//

#include "ConcreteFactory.h"
#include "../View/Entities/DynamicEntities/PacmanView.h"
#include "../View/Entities/DynamicEntities/GhostView.h"

using namespace Logic;
using namespace View;

std::shared_ptr<PacmanEntity> ConcreteFactory::CreatePacman(const Vector2f& position, float speed) const {
    auto entityModel = std::make_shared<PacmanEntity>(EntityType::Pacman, position, speed);
    auto entityView = std::make_shared<PacmanView>(entityModel);
    entityModel->Attach(entityView);
    return entityModel;
}

std::shared_ptr<GhostEntity> ConcreteFactory::CreateGhost(const Vector2f& position, float speed) const {
    auto entityModel = std::make_shared<GhostEntity>(EntityType::Ghost, position, speed);
    auto entityView = std::make_shared<GhostView>(entityModel);

    entityModel->Attach(entityView);
    return entityModel;
}


std::shared_ptr<EntityModel> ConcreteFactory::CreateWall(const Vector2f& position) const {
    auto entityModel = std::make_shared<WallEntity>(EntityType::Wall, position);
    auto entityView = std::make_shared<WallView>(entityModel);
    entityModel->Attach(entityView);
    return entityModel;
}

std::shared_ptr<CollectableEntity> ConcreteFactory::CreateCoin(const Vector2f& position) const {
    auto entityModel = std::make_shared<CoinEntity>(EntityType::Coin, position, true);
    auto entityView = std::make_shared<CoinView>(entityModel);
    entityModel->Attach(entityView);
    return entityModel;
}

std::shared_ptr<CollectableEntity> ConcreteFactory::CreateFruit(const Vector2f& position) const {
    auto entityModel = std::make_shared<FruitEntity>(EntityType::Fruit, position, true);
    auto entityView = std::make_shared<FruitView>(entityModel);
    entityModel->Attach(entityView);
    return entityModel;
}

std::shared_ptr<BananaEntity> ConcreteFactory::CreateBanana(const Vector2f& position) const {
    auto entityModel = std::make_shared<BananaEntity>(EntityType::Banana, position, true);
    auto entityView = std::make_shared<FruitView>(entityModel);
    entityModel->Attach(entityView);
    return entityModel;
}

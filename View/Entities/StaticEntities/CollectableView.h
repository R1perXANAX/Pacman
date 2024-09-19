//
// Created by R1perXNX on 7/3/2024.
//

#ifndef PACMANV2_COLLECTABLEVIEW_H
#define PACMANV2_COLLECTABLEVIEW_H

#include "../EntityView.h"
#include "../../../Logic/Entities/StaticEntities/CollectableEntity.h"

namespace View {
class WallView final : public EntityView<Logic::WallEntity> {
    sf::RectangleShape rectangleShape;

public:
    WallView(const std::shared_ptr<Logic::WallEntity>& model);
    void Draw() override;
    ~WallView() override = default;
};

class CoinView final : public EntityView<Logic::CoinEntity> {
    sf::CircleShape circleShape;

public:
    CoinView(const std::shared_ptr<Logic::CoinEntity>& model);
    void Draw() override;
    ~CoinView() override = default;
};

enum class FruitType {
    Apple,
    Banana,
};

class FruitView final : public EntityView<Logic::FruitEntity> {
    sf::Texture texture;
    sf::IntRect textureRect;
    sf::Sprite sprite;

public:
    FruitView(const std::shared_ptr<Logic::FruitEntity>& model);
    void Draw() override;
    ~FruitView() override = default;
};
}


#endif //PACMANV2_COLLECTABLEVIEW_H
